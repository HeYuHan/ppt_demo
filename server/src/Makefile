debug:
	$(MAKE) -C common
	$(MAKE) -C test_server

release:
	$(MAKE) RELEASE=1 -C common
	$(MAKE) RELEASE=1 -C test_server

clean:
	$(MAKE) clean -C common
	$(MAKE) clean -C test_server