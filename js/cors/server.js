const express = require('express');
const app = express();
const cors = require('cors');
const data = require('./data.json');

app.use(cors());

app.get('/data', (req, res) => {
  res.json(data);
});

app.listen(3000, () => {
  console.log('Server listening on port 3000');
});

