const fs = require('fs');
const grpc = require('@grpc/grpc-js');
const protoLoader = require('@grpc/proto-loader');

const GRPC_HOST = 'localhost:10009'
const MACAROON_PATH = 'LND_DIR/data/chain/bitcoin/regtest/admin.macaroon'
const TLS_PATH = 'LND_DIR/tls.cert'

const loaderOptions = {
  keepCase: true,
  longs: String,
  enums: String,
  defaults: true,
  oneofs: true,
};
const packageDefinition = protoLoader.loadSync(['lightning.proto', 'invoicesrpc/invoices.proto'], loaderOptions);
const invoicesrpc = grpc.loadPackageDefinition(packageDefinition).invoicesrpc;
process.env.GRPC_SSL_CIPHER_SUITES = 'HIGH+ECDSA';
const tlsCert = fs.readFileSync(TLS_PATH);
const sslCreds = grpc.credentials.createSsl(tlsCert);
const macaroon = fs.readFileSync(MACAROON_PATH).toString('hex');
const macaroonCreds = grpc.credentials.createFromMetadataGenerator(function(args, callback) {
  let metadata = new grpc.Metadata();
  metadata.add('macaroon', macaroon);
  callback(null, metadata);
});
let creds = grpc.credentials.combineChannelCredentials(sslCreds, macaroonCreds);
let client = new invoicesrpc.Invoices(GRPC_HOST, creds);
let request = {
  memo: <string>,
  hash: <bytes>,
  value: <int64>,
  value_msat: <int64>,
  description_hash: <bytes>,
  expiry: <int64>,
  fallback_addr: <string>,
  cltv_expiry: <uint64>,
  route_hints: <RouteHint>,
  private: <bool>,
};
client.addHoldInvoice(request, function(err, response) {
  console.log(response);
});
// Console output:
//  {
//    "payment_request": <string>,
//    "add_index": <uint64>,
//    "payment_addr": <bytes>,
//  }
