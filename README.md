# Simple-Shell
A simple linux shell written in C++

Some commands are written using the filesystem library, other are implemented from scratch. 

# Commands to implement
- [x] ls
- [x] cd
- [x] pwd
- [x] cat
- [ ] mkdir
- [ ] rm
- [ ] mv
- [ ] cp
- [ ] fake-vim (custom text editor)

## TODO

- [ ] Options Parser
- [ ] Output redirection 
- [ ] Output Piping
- [ ] Signal Handler

# Limitations

- cat won't work if no file is specified. That's because std::cin blocks signal catching
- cd if no dir is specified does nothing. In the future this behavior will change to work like the "real" cd
