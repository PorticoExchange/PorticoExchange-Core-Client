async function updatePrice(price) {
  const timestamp = Date.now()
  const entry = {
    timestamp,
    price
  }
  await db.put(timestamp.toString(), entry)
}
