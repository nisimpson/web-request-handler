#!/bin/bash
lighttpd -f lighttpd/lighttpd.conf
ps aux | grep lighttpd