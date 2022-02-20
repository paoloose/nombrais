const express = require('express');
const favicon = require('serve-favicon');
const path = require('path');
const EXPRESS_PORT = 3001;

// ⚪ express js ---->
const app = express();
const cors = require('cors')
const generator = require('./build/Release/generator');

app.use(cors());
app.use(favicon(path.join(__dirname, 'public', 'favicon.ico')));

// Logged information
app.use((req, res, next) => {
  console.log(`Request '${req.method}' received at PORT: ${req.socket.remotePort},`);
  console.log(` for ${req.path}`);
  next();
})

// Home
app.get('/', (req, res) => {
  let name_example = generator.generateName(3, 6, '');
  let object_example = `
  {
    seed: ${generator.getSeedFormat(name_example)},
    name: ${name_example}
  }
  `;
  res.send(`
    <div style="display: flex;flex-direction: column;align-items: center;">
      <h1>Welcome to the Nombrais API</h1>
      <div>We are glad to see you here!</div><br>
      <div>Request example:</div>
      <pre style='word-wrap: break-word; white-space: pre-wrap;'>${object_example}</pre>
      <div>Visit us on <a href="https://github.com/leflores-fisi/nombrais" target="__BLANK">github</a></div>
    </div>
  `);
});


// API names requests
const GET_NAMES = {
  option1: (quantity, length) => {
    let random_names = [];
    for (let i = 0; i < quantity; i++) {
      let name = generator.generateName(Number(length), Number(length), '');
      random_names.push({
        seed: generator.getSeedFormat(name),
        name: name
      });
    }
    return random_names;
  },
  option2: (quantity, min_length, max_length) => {
    let random_names = [];
    for (let i = 0; i < quantity; i++) {
      let name = generator.generateName(Number(min_length), Number(max_length), '');
      random_names.push({
        seed: generator.getSeedFormat(name),
        name: name
      });
    }
    return random_names;
  },
  option3: (quantity, seed) => {
    let random_names = [];
    for (let i = 0; i < quantity; i++) {
      let name = generator.generateNameFromSeed(seed);
      random_names.push({
        seed: seed,
        name: name
      });
    }
  }
};
app.get('/api/v1.0/names', (req, res) => {

  let isBadRequest = false;
  let random_names = [];
  const {quantity, seed, min_length, max_length, length} = req.query

  if (isNaN(quantity) || (quantity < 1 || quantity > 100)) isBadRequest = true;

  // Names request [option 1]
  if ((quantity && length) && (min_length === undefined && max_length == undefined && seed === undefined)) {

    if (isNaN(length)) isBadRequest = true;
    else random_names = GET_NAMES['option1'](quantity, length);
  }
  // Names request [option 2]
  else if ((quantity && min_length && max_length) && (seed === undefined && length === undefined)) {

    if (isNaN(min_length) || isNaN(max_length)) isBadRequest = true;
    else if (Number(min_length) > Number(max_length)) isBadRequest = true;
    else random_names = GET_NAMES['option2'](quantity, min_length, max_length);
  }
  // Names request [option 3]
  else if ((quantity && seed) && (min_length === undefined && max_length == undefined && length === undefined)) {

    if (seed.split('').filter(letter => letter !== '0' && letter !== '1').length > 0) isBadRequest = true;
    else random_names = GET_NAMES['option3'](quantity, seed);
  }
  else isBadRequest = true

  console.log('Request query:', req.query);

  if (isBadRequest) res.status(400).json([]) // bad request http code
  else res.status(200).json(random_names); // ok 👍
});

// Final middleware (404 error)
app.use((req, res) => {
  const random_name = generator.generateName(5, 6, '');
  console.log(`Error: reached final middleware, 404 error thrown for path: ${req.path}`);
  res.status(404);
  res.send(`
    <div style="display: flex;flex-direction: column;align-items: center;">
      <img src="https://http.cat/404.jpg" width="750" height="600" style="background-color: black"></img>
      <div>Path: '${req.path}' was not founded</div>
      <div>But so you don't leave with nothing, take a random name: ${random_name}</div>
    </div>
  `);
})

// Running app
app.listen(EXPRESS_PORT);
console.log('Node server running on port', EXPRESS_PORT);
