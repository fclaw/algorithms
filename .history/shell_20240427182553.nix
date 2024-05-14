let
   pkgs = import (fetchTarball "https://github.com/NixOS/nixpkgs/archive/nixos-23.11.tar.gz") {};
   golang = pkgs.gcc;
in
pkgs.mkShell {

  buildInputs = [ golang ];
  NIX_PATH = "nixpkgs=" + pkgs.path;
  shellHook = ''
    export PATH="$HOME/go/bin:$PATH"
    go install golang.org/x/tools/cmd/goimports@latest
   '';
  }