let
   pkgs = import (fetchTarball "https://github.com/NixOS/nixpkgs/archive/nixos-24.05.tar.gz") {};
   clang = pkgs.gcc;
   py = pkgs.python3;
in
pkgs.mkShell {
  buildInputs = [ clang pkgs.boost py (py.withPackages (ps: [ps.numpy])) ];
  NIX_PATH = "nixpkgs=" + pkgs.path;
  }