{ config, lib, pkgs, ... }:

with lib;
let
  options.services.clightning = {
    enable = mkEnableOption "clightning, a Lightning Network implementation in C";
    address = mkOption {
      type = types.str;
      default = "127.0.0.1";
      description = mdDoc "Address to listen for peer connections.";
    };
    port = mkOption {
      type = types.port;
      default = 9735;
      description = mdDoc "Port to listen for peer connections.";
    };
    proxy = mkOption {
      type = types.nullOr types.str;
      default = if cfg.tor.proxy then config.nix-bitcoin.torClientAddressWithPort else null;
      description = mdDoc ''
        Socks proxy for connecting to Tor nodes (or for all connections if option always-use-proxy is set).
      '';
    };
    always-use-proxy = mkOption {
      type = types.bool;
      default = cfg.tor.proxy;
      description = mdDoc ''
        Always use the proxy, even to connect to normal IP addresses.
        You can still connect to Unix domain sockets manually.
        This also disables all DNS lookups, to avoid leaking address information.
      '';
    };
    dataDir = mkOption {
      type = types.path;
      default = "/var/lib/clightning";
      description = mdDoc "The data directory for clightning.";
    };
    networkDir = mkOption {
      readOnly = true;
      default = "${cfg.dataDir}/${network}";
      description = mdDoc "The network data directory.";
    };
    wallet = mkOption {
      type = types.nullOr types.str;
      default = null;
      example = "sqlite3:///var/lib/clightning/bitcoin/lightningd.sqlite3";
      description = mdDoc ''
        Wallet data scheme (sqlite3 or postgres) and location/connection
        parameters, as fully qualified data source name.
      '';
    };
    extraConfig = mkOption {
