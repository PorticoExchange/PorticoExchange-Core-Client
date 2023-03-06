async function getCurrentPrice() {
  const iterator = db.iterator({
    gte: '0',
    reverse: true
  })
  const result = await iterator.next()
  if (result) {
    return result.value.price
  } else {
    return null
  }
}
