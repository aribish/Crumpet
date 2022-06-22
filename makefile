crumpet: interpreter.cpp
	g++ $< -o $@
crumpet-db: interpreter.cpp
	g++ $<  -o $@ -D DEBUG
