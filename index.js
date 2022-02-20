const express = require('express');
const cors = require('cors')
const favicon = require('serve-favicon');
const path = require('path');
const EXPRESS_PORT = process.env.PORT || 3001;

// ⚪ express js ---->
const app = express();
const generator = require('./build/Release/generator');

// Helpers
const capitalize = (str) => str && str[0].toUpperCase() + str.slice(1);

app.use(cors());
app.use(favicon(path.join(__dirname, 'public', 'favicon.ico')));

// Logged information
app.use((req, res, next) => {
  console.log(`Request '${req.method}' received at PORT: ${req.socket.remotePort} for ${req.path}`);
  next();
})

// Home
app.get('/', (req, res) => {
  let name_example = generator.generateName(4, 7, '');
  let object_example = `
{
  seed: ${generator.getSeedFormat(name_example)},
  name: ${name_example}
}
  `;
  res.send(`
    <div style="display: flex;flex-direction: column;align-items: center;font-size: 20px;padding:20px">
      <h1>Welcome to Nombrais API</h1>
      <div>✨ Simple customizable random names generator REST API ✨</div><br>
      <pre style='word-wrap:break-word;white-space:pre-wrap;background-color:#EDECEF;padding:0 25px;border-radius:5px'><code>${object_example}</code></pre>
      <div>Visit our <a href="https://github.com/leflores-fisi/nombrais" target="__BLANK">github repository</a> for examples</div>
      <div>or make a <a href="https://nombrais.herokuapp.com/api/names?quantity=10&min_length=3&max_length=6" target="__BLANK">quick request</a>.</div>
    </div>
  `);
});


// API names requests
const GET_NAMES = {
  option1: (quantity, length, capitalized) => {
    let random_names = [];
    for (let i = 0; i < quantity; i++) {
      let name = generator.generateName(Number(length), Number(length), '');
      random_names.push({
        seed: generator.getSeedFormat(name),
        name: capitalized ? capitalize(name) : name
      });
    }
    return random_names;
  },
  option2: (quantity, min_length, max_length, capitalized) => {
    let random_names = [];
    for (let i = 0; i < quantity; i++) {
      let name = generator.generateName(Number(min_length), Number(max_length), '');
      random_names.push({
        seed: generator.getSeedFormat(name),
        name: capitalized ? capitalize(name) : name
      });
    }
    return random_names;
  },
  option3: (quantity, seed, capitalized) => {
    let random_names = [];
    for (let i = 0; i < quantity; i++) {
      let name = generator.generateNameFromSeed(seed);
      random_names.push({
        seed: seed,
        name: capitalized ? capitalize(name) : name
      });
    }
    return random_names;
  }
};
app.get('/api/names', (req, res) => {

  let isBadRequest = false;
  let random_names = [];
  const {quantity, seed, min_length, max_length, length, capitalized} = req.query

  if (isNaN(quantity) || (quantity < 1 || quantity > 150)) isBadRequest = true;

  // Names request [option 1]
  if ((quantity && length) && (min_length === undefined && max_length == undefined && seed === undefined)) {

    if (isNaN(length)) isBadRequest = true;
    else random_names = GET_NAMES['option1'](quantity, length, capitalized || false);
  }
  // Names request [option 2]
  else if ((quantity && min_length && max_length) && (seed === undefined && length === undefined)) {

    if (isNaN(min_length) || isNaN(max_length)) isBadRequest = true;
    else if (Number(min_length) > Number(max_length)) isBadRequest = true;
    else random_names = GET_NAMES['option2'](quantity, min_length, max_length, capitalized || false);
  }
  // Names request [option 3]
  else if ((quantity && seed) && (min_length === undefined && max_length == undefined && length === undefined)) {

    if (seed.split('').filter(letter => letter !== '0' && letter !== '1').length > 0) isBadRequest = true;
    else random_names = GET_NAMES['option3'](quantity, seed, capitalized || false);
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
    <div style="display: flex;flex-direction: column;align-items: center;font-size: 20px;padding:20px">
      <img src="https://http.cat/404.jpg" width="375" height="300" style="background-color: black"></img>
      <div>We are sorry 😔 This route does'nt match with any of ours</div>
      <hr>
      <div>Visit our <a href="https://github.com/leflores-fisi/nombrais" target="__BLANK">github repository</a> for guidance and a hug</div>
      <hr>
      <div>Name for consolation: <code>${random_name}</code></div>
    </div>
  `);
})

// Running app
app.listen(EXPRESS_PORT);
console.log('Server running on port', EXPRESS_PORT);
