# M4OEP-cchrist7-qwarden

## Installing sfml with Brew (MacOS)
```brew install sfml```


## Compiling sfml.cpp on MacOS
### Run the shell script with the following command to create "run" executable:
```sh compile.sh```
### Or traditionally:
``` g++ sfml.cpp -I/opt/homebrew/Cellar/sfml/2.5.1_1/include -o run -L/opt/homebrew/Cellar/sfml/2.5.1_1/lib -lsfml-graphics -lsfml-window -lsfml-system```
