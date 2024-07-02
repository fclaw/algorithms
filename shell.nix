let
   pkgs = import (fetchTarball "https://github.com/NixOS/nixpkgs/archive/nixos-24.05.tar.gz") {};
   clang = pkgs.gcc;
in
pkgs.mkShell {

  buildInputs = [ clang ];
  NIX_PATH = "nixpkgs=" + pkgs.path;
  }