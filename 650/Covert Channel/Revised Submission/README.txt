*** FOR LINUX ONLY ***

Compile using gcc and run bury.c with your html file and confidential file as inputs. It will write an 'output.html' file which will contain the secret message. 

Compile using gcc and run resurrect.c with your secret html file as input. It will write a 'secret.txt' file which will contain the secret message contained in the secret html file provided.

# BURY 
gcc -o run bury.c
./run <input file> <confidential file>

# RESURRECT
gcc -o run resurrect.c -lm
./run <input file>
