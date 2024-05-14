let
   pkgs = import (fetchTarball "https://github.com/NixOS/nixpkgs/archive/nixos-23.11.tar.gz") {};
   clang = pkgs.gcc;
in
pkgs.mkShell {

  buildInputs = [ clang ];
  NIX_PATH = "nixpkgs=" + pkgs.path;
  shellHook = ''
    export PATH="$HOME/go/bin:$PATH"
    go install golang.org/x/tools/cmd/goimports@latest
   '';
  }