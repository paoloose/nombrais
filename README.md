## Nombrais API
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)<br>
✨ Simple customizable random names generator REST API ✨

#### Examples:
### Option 1
```js
fetch('http://localhost:3001/api/v1.0/names?quantity=2&length=5')
  .then(response => response.json())
  .then(names => console.log(names));

```
Outputs 👇
```js
[
  {
    seed: '10100',
    name: 'damoa'
  },
  {
    seed: '11011',
    name: 'trist'
  }
]
```
<br>

### Option 2
```js
fetch('http://localhost:3001/api/v1.0/names?quantity=2&min_length=3&max_length=5')
  .then(response => response.json())
  .then(names => console.log(names));

```
Outputs 👇
```js
[
  {
    seed: '010',
    name: 'ere'
  },
  {
    seed: '10101',
    name: 'lihes'
  }
]
```
<br>

### Option 3
```js
fetch('http://localhost:3001/api/v1.0/names?quantity=2&seed=1010111')
  .then(response => response.json())
  .then(names => console.log(names));

```
Outputs 👇
```js
[
  {
    seed: '1010111',
    name: 'tiwatny'
  },
  {
    seed: '1010111',
    name: 'yaridrc'
  }
]
```
<br>
<hr>

### Aditionals:
- Add argument `&capitalized=true` to capitalize the first character of the names
