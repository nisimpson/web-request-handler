#!/bin/bash
lighttpd -D -f lighttpd/lighttpd.conf
ps aux | grep lighttpd