
/* A simple program to test the text rendering feature of the TTF library */

#include <stdio.h>

#include "SDL.h"
#include "SDL_ttf.h"

#define DEFAULT_PTSIZE	18
#define DEFAULT_TEXT	"The quick brown fox jumped over the lazy dog"

static char *Usage =
"Usage: %s [-utf8|-unicode] [-b] [-i] [-u] <font>.ttf [ptsize] [text]\n";

main(int argc, char *argv[])
{
	char *argv0 = argv[0];
	SDL_Surface *screen;
	TTF_Font *font;
	SDL_Surface *text, *temp;
	int ptsize;
	int i, done;
	int rdiff, gdiff, bdiff;
	SDL_Color colors[5];
	SDL_Color white = { 0xFF, 0xFF, 0xFF, 0 };
	SDL_Color black = { 0x00, 0x00, 0x00, 0 };
	SDL_Rect dstrect;
	SDL_Event event;
	int rendersolid;
	int renderstyle;
	enum {
		RENDER_LATIN1,
		RENDER_UTF8,
		RENDER_UNICODE
	} rendertype;
	char *message, string[128];

	/* Look for special rendering types */
	rendersolid = 0;
	renderstyle = TTF_STYLE_NORMAL;
	rendertype = RENDER_LATIN1;
	for ( i=1; argv[i] && argv[i][0] == '-'; ++i ) {
		if ( strcmp(argv[i], "-solid") == 0 ) {
			rendersolid = 1;
		} else
		if ( strcmp(argv[i], "-utf8") == 0 ) {
			rendertype = RENDER_UTF8;
		} else
		if ( strcmp(argv[i], "-unicode") == 0 ) {
			rendertype = RENDER_UNICODE;
		} else
		if ( strcmp(argv[i], "-b") == 0 ) {
			renderstyle |= TTF_STYLE_BOLD;
		} else
		if ( strcmp(argv[i], "-i") == 0 ) {
			renderstyle |= TTF_STYLE_ITALIC;
		} else
		if ( strcmp(argv[i], "-u") == 0 ) {
			renderstyle |= TTF_STYLE_UNDERLINE;
		} else {
			fprintf(stderr, Usage, argv0);
			exit(1);
		}
	}
	argv += i;
	argc -= i;

	/* Check usage */
	if ( ! argv[0] ) {
		fprintf(stderr, Usage, argv0);
		exit(1);
	}

	/* Initialize SDL */
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
		fprintf(stderr, "Couldn't initialize SDL: %s\n",SDL_GetError());
		exit(2);
	}
	atexit(SDL_Quit);

	/* Initialize the TTF library */
	if ( TTF_Init() < 0 ) {
		fprintf(stderr, "Couldn't initialize TTF: %s\n",SDL_GetError());
		exit(2);
	}
	atexit(TTF_Quit);

	/* Set a 640x480x8 video mode */
	screen = SDL_SetVideoMode(640, 480, 8, SDL_SWSURFACE);
	if ( screen == NULL ) {
		fprintf(stderr, "Couldn't set 640x480x8 video mode: %s\n",
							SDL_GetError());
		exit(2);
	}

	/* Set a palette that is good for black text */
	rdiff = white.r - black.r;
	gdiff = white.g - black.g;
	bdiff = white.b - black.b;
	for ( i=0; i<5; ++i ) {
		colors[i].r = black.r + (i*rdiff)/4;
		colors[i].g = black.g + (i*gdiff)/4;
		colors[i].b = black.b + (i*bdiff)/4;
	}
	SDL_SetColors(screen, colors, 10, 5);

	/* Clear the background to white */
	SDL_FillRect(screen, NULL,
			SDL_MapRGB(screen->format, white.r, white.g, white.b));
	SDL_UpdateRect(screen, 0, 0, 0, 0);

	/* Open the font file with the requested point size */
	ptsize = 0;
	if ( argc > 1 ) {
		ptsize = atoi(argv[1]);
	}
	if ( ptsize == 0 ) {
		i = 2;
		ptsize = DEFAULT_PTSIZE;
	} else {
		i = 3;
	}
	font = TTF_OpenFont(argv[0], ptsize);
	if ( font == NULL ) {
		fprintf(stderr, "Couldn't load %d pt font from %s: %s\n",
					ptsize, argv[0], SDL_GetError());
		exit(2);
	}
	TTF_SetFontStyle(font, renderstyle);

	/* Show which font file we're looking at */
	sprintf(string, "Font file: %s", argv[0]);  /* possible overflow */
	if ( rendersolid ) {
		text = TTF_RenderText_Solid(font, string, black);
	} else {
		text = TTF_RenderText_Shaded(font, string, black, white);
	}
	if ( text != NULL ) {
		dstrect.x = 4;
		dstrect.y = 4;
		dstrect.w = text->w;
		dstrect.h = text->h;
		SDL_BlitSurface(text, NULL, screen, &dstrect);
		SDL_FreeSurface(text);
	}
	
	/* Render and center the message */
	if ( argc > 2 ) {
		message = argv[2];
	} else {
		message = DEFAULT_TEXT;
	}
	switch (rendertype) {
	    case RENDER_LATIN1:
		if ( rendersolid ) {
			text = TTF_RenderText_Solid(font,message,black);
		} else {
			text = TTF_RenderText_Shaded(font,message,black,white);
		}
		break;

	    case RENDER_UTF8:
		if ( rendersolid ) {
			text = TTF_RenderUTF8_Solid(font,message,black);
		} else {
			text = TTF_RenderUTF8_Shaded(font,message,black,white);
		}
		break;

	    case RENDER_UNICODE:
		{
			/* This doesn't actually work because you can't pass
			   UNICODE text in via command line, AFAIK, but...
			 */
			Uint16 unicode_text[BUFSIZ];
			int index;
			for ( index = 0; (message[0] || message[1]); ++index ) {
				unicode_text[index]  = ((Uint8 *)message)[0];
				unicode_text[index] <<= 8;
				unicode_text[index] |= ((Uint8 *)message)[1];
				message += 2;
			}
			if ( rendersolid ) {
				text = TTF_RenderUNICODE_Solid(font,
					unicode_text, black);
			} else {
				text = TTF_RenderUNICODE_Shaded(font,
					unicode_text, black, white);
			}
		}
		break;
	    default:
		text = NULL; /* This shouldn't happen */
		break;
	}
	if ( text == NULL ) {
		fprintf(stderr, "Couldn't render text: %s\n", SDL_GetError());
		TTF_CloseFont(font);
		exit(2);
	}
	dstrect.x = (screen->w - text->w)/2;
	dstrect.y = (screen->h - text->h)/2;
	dstrect.w = text->w;
	dstrect.h = text->h;
	printf("Font is generally %d big, and string is %hd big\n",
						TTF_FontHeight(font), text->h);

	/* Blit the text surface */
	if ( SDL_BlitSurface(text, NULL, screen, &dstrect) < 0 ) {
		fprintf(stderr, "Couldn't blit text to display: %s\n", 
								SDL_GetError());
		TTF_CloseFont(font);
		exit(2);
	}
	SDL_UpdateRect(screen, 0, 0, 0, 0);

	/* Set the text colorkey and convert to display format */
	if ( SDL_SetColorKey(text, SDL_SRCCOLORKEY|SDL_RLEACCEL, 0) < 0 ) {
		fprintf(stderr, "Warning: Couldn't set text colorkey: %s\n",
								SDL_GetError());
	}
	temp = SDL_DisplayFormat(text);
	if ( temp != NULL ) {
		SDL_FreeSurface(text);
		text = temp;
	}

	/* Wait for a keystroke, and blit text on mouse press */
	done = 0;
	while ( ! done ) {
		if ( SDL_WaitEvent(&event) < 0 ) {
			fprintf(stderr, "SDL_PullEvent() error: %s\n",
								SDL_GetError());
			done = 1;
			continue;
		}
		switch (event.type) {
			case SDL_MOUSEBUTTONDOWN:
				dstrect.x = event.button.x - text->w/2;
				dstrect.y = event.button.y - text->h/2;
				dstrect.w = text->w;
				dstrect.h = text->h;
				if ( SDL_BlitSurface(text, NULL, screen,
							&dstrect) == 0 ) {
					SDL_UpdateRects(screen, 1, &dstrect);
				} else {
					fprintf(stderr,
					"Couldn't blit text to display: %s\n", 
								SDL_GetError());
				}
				break;
				
			case SDL_KEYDOWN:
			case SDL_QUIT:
				done = 1;
				break;
			default:
				break;
		}
	}
	SDL_FreeSurface(text);
	TTF_CloseFont(font);
	exit(0);
}
