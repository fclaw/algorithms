let
   pkgs = import (fetchTarball "https://github.com/NixOS/nixpkgs/archive/nixos-26.05.tar.gz") {};
   clang = pkgs.gcc14;
   py = pkgs.python3;
   git = pkgs.git; 
in
pkgs.mkShell {
  buildInputs = [ git clang pkgs.boost py (py.withPackages (ps: [ps.numpy])) ];
  NIX_PATH = "nixpkgs=" + pkgs.path;
  }