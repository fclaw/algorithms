let
   pkgs = import (fetchTarball "https://github.com/NixOS/nixpkgs/archive/nixos-23.11.tar.gz") {};
   golang = pkgs.go; 
  #  ps = import ./purescript.nix { inherit pkgs; };
in
pkgs.mkShell {

  buildInputs = [ golang ];
  NIX_PATH = "nixpkgs=" + pkgs.path;
  shellHook = ''
   '';
  }