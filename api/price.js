const express = require('express')
const app = express()

app.get('/price', async function(req, res) {
  const price = await getCurrentPrice()
  if (price) {
    res.json({
      price
    })
  } else {
    res.status(404).send('Price not found')
  }
})

app.listen(3000, function() {
  console.log('API listening on port 3000')
})

