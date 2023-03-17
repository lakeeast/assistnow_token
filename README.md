## How to build
mkdir build
cd build
cmake ..
make

# Check in steps
eval "$(ssh-agent -s)"
ssh-add ~/.ssh/id_ed25519
