const express = require('express');
const favicon = require('serve-favicon');
const path = require('path');
const EXPRESS_PORT = 3001;

// ⚪ express js ---->
const app = express();
const cors = require('cors')
const generator = require('./build/Release/generateName')

app.use(cors());
app.use(favicon(path.join(__dirname, 'public', 'favicon.ico')));

// Request information
app.use((req, res, next) => {
  console.log(`Request '${req.method}' received at PORT: ${req.socket.remotePort},`);
  console.log(` for ${req.path}`);
  next();
})

// Home
app.get('/', (req, res) => {
  let name_example = generator.generateName(3, 6, '')
  let object_example = `
  {
    seed: ${generator.getSeedFormat(name_example)},
    name: ${name_example}
  }
  `
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

app.get('/api/generate=:num&min=:min-length&max-length=:max', (req, res) => {

  // If the given argument if not a number
  if (isNaN(req.params.num)) {
    res.send(`
      <div style="display: flex;flex-direction: column;align-items: center;">
        <img src="https://http.cat/400.jpg" width="750" height="600" style="background-color: black"></img>
        <div>Expected argument generate= to be number</div>
      </div>
    `);
    res.status(400).end();
  }
  // If the names requests exceeds 100
  else if (req.params.num < 1 || req.params.num > 100) {
    res.send(`
      <div style="display: flex;flex-direction: column;align-items: center;">
        <img src="https://http.cat/400.jpg" width="750" height="600" style="background-color: black"></img>
        <div>Argument quantity out of bounds</div>
      </div>
    `);
    res.status(400).end();
  }
  else {

    // Creating response the object
    let random_names = []
    for (let i = 0; i < req.params.num; i++) {
      let name = generator.generateName(Number(req.params.min), Number(req.params.max), '')
      random_names.push({
        seed: generator.getSeedFormat(name),
        name: name
      });
    }
    console.log('Generating names with params:', req.params);
    res.status(200);
    res.json(random_names);
  }

});

app.get('/api/generate=:num/seed=:seed', (req, res, next) => {

  // If the quantity if not a number
  if (isNaN(req.params.num)) {
    res.send(`
      <div style="display: flex;flex-direction: column;align-items: center;">
        <img src="https://http.cat/400.jpg" width="750" height="600" style="background-color: black"></img>
        <div>Expected argument generate= to be number</div>
      </div>
    `);
    res.status(400).end();
  }
  // If the names requests exceeds 100
  else if (req.params.num > 100) {
    res.send(`
      <div style="display: flex;flex-direction: column;align-items: center;">
        <img src="https://http.cat/400.jpg" width="750" height="600" style="background-color: black"></img>
        <div>Argument quantity exceeds the limit (100)</div>
      </div>
    `);
    res.status(400).end();
  }
  // If the seed contains other characters that are not binaries ('0' for vowel, '1' for consonant)
  else if (req.params.seed.split('').filter(letter => letter !== '0' && letter !== '1').length > 0) {
    res.send(`
      <div style="display: flex;flex-direction: column;align-items: center;">
        <img src="https://http.cat/400.jpg" width="750" height="600" style="background-color: black"></img>
        <div>Expected argument seed= to have binary format (0 for vowel, 1 for consonant) but get "${req.params.seed}"</div>
      </div>
    `);
    res.status(400).end();
  }
  else {
    // All OK, Creating response the object
    res.status(200)
    let random_names = []

    for (let i = 0; i < req.params.num; i++) {
      let name = generator.generateNameFromSeed(req.params.seed);
      random_names.push({
        seed: req.params.seed,
        name: name
      });
    }
    res.json(random_names)
  }

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
