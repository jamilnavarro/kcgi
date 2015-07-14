/*	$Id$ */
/*
 * Copyright (c) 2014, 2015 Kristaps Dzonsons <kristaps@bsd.lv>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "kcgi.h"

int
main(int argc, char *argv[])
{
	struct kreq	 req;
	struct kfcgi	*fcgi;
	enum kcgi_err	 er;
	const char	*pname;

	if ((pname = strrchr(argv[0], '/')) == NULL)
		pname = argv[0];
	else
		++pname;

	fprintf(stderr, "%s: initialising...\n", pname);

	if (KCGI_OK != khttp_fcgi_init(&fcgi, NULL, 0))
		return(EXIT_FAILURE);

	fprintf(stderr, "%s: looping...\n", pname);
	
	for (;;) {
		er = khttp_fcgi_parse(fcgi, &req, NULL, 0, 0);
		if (KCGI_HUP == er) {
			fprintf(stderr, "%s: hup\n", pname);
			khttp_free(&req);
			break;
		} else if (KCGI_OK != er) {
			fprintf(stderr, "%s: badness\n", pname);
			khttp_free(&req);
			break;
		}
		fprintf(stderr, "%s: whee!\n", pname);
		khttp_free(&req);
	}

	fprintf(stderr, "%s: outing\n", pname);
	khttp_fcgi_free(fcgi);
	return(EXIT_SUCCESS);
}

