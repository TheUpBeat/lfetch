lfetch: lfetch.c
	$(CC) lfetch.c -o lfetch

install:
	@cp -p lfetch $(DESTDIR)$(PREFIX)/bin/lfetch
	@chmod 755 $(DESTDIR)$(PREFIX)/bin/lfetch

uninstall:
	@rm -rf $(DESTDIR)$(PREFIX)/bin/lfetch
