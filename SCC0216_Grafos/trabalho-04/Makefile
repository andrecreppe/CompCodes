all:

run:
	@python3 main.py

test: test1 test2

test1:
	@python3 main.py < ./test/$(subst test,,$@).in > ./test/$(subst test,,$@)t.out
	@diff ./test/$(subst test,,$@)t.out ./test/$(subst test,,$@).out 
	
test2:
	@python3 main.py < ./test/$(subst test,,$@).in > ./test/$(subst test,,$@)t.out
	@diff ./test/$(subst test,,$@)t.out ./test/$(subst test,,$@).out 

zip:
	zip -r t4.zip *.py

.PHONY: all run	
.IGNORE: test1 test2