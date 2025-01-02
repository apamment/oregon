#if WIN32
#   define _MSC_VER 1
#	define _CRT_SECURE_NO_WARNINGS
#   include <windows.h>
#   define strcasecmp _stricmp
#else

#endif
#include <OpenDoor.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct high_scores {
	int score;
	char name[32];
	time_t timestamp;
};

void create_scorefile() {
	FILE *fptr;
	struct high_scores hs[10];
	int i;

	fptr = fopen("players.idx", "w");
	if (!fptr) {
		return;
	}
	for (i = 0; i < 10; i++) {
		hs[i].score = 0;
		strcpy(hs[i].name, "Nobody");
		hs[i].timestamp = time(NULL);
		fwrite(&hs[i], sizeof(struct high_scores), 1, fptr);
	}
	fclose(fptr);
}

int add_highscore(int score) {
	FILE *fptr;
	time_t wait_time = time(NULL);
	struct high_scores hs[10];
	struct high_scores temp;
	int i, j;

	do {
		fptr = fopen("players.idx", "r");
		if (fptr != NULL) {
			break;
		}
		if (errno == ENOENT) {
			create_scorefile();
			od_kernel();
			continue;
		}
		if (errno != EACCES || wait_time + 10 <= time(NULL)) {
			break;
		}
		od_kernel();
	} while (!fptr);

	if (!fptr) {
		od_printf("\r\n\r\n`bright red`Error opening score file...\r\n");
		return 0;
	}

	for (i = 0; i < 10; i++) {
		fread(&hs[i], sizeof(struct high_scores), 1, fptr);
	}
	fclose(fptr);

	if (hs[9].score < score) {
		hs[9].score = score;
		strncpy(hs[9].name, od_control_get()->user_name, 31);
		hs[9].timestamp = time(NULL);
	}
	else {
		return 0;
	}

	for (i = 0; i < 10; ++i) {
		for (j = i + 1; j < 10; ++j) {
			if (hs[i].score < hs[j].score) {
				temp = hs[i];
				hs[i] = hs[j];
				hs[j] = temp;
			}
		}
	}

	wait_time = time(NULL);

	do {
		fptr = fopen("players.idx", "w");
		if (fptr != NULL) {
			break;
		}
		if (errno != EACCES || wait_time + 10 <= time(NULL)) {
			break;
		}
		od_kernel();
	} while (!fptr);

	if (!fptr) {
		od_printf("\r\n\r\n`bright red`Error opening score file...\r\n");
		return 0;
	}

	for (i = 0; i < 10; i++) {
		fwrite(&hs[i], sizeof(struct high_scores), 1, fptr);
	}
	fclose(fptr);
	return 1;
}

void show_highscores() {
	FILE *fptr;
	time_t wait_time = time(NULL);
	struct high_scores hs[10];
	struct tm timetm;
	int i;

	do {
		fptr = fopen("players.idx", "r");
		if (fptr != NULL) {
			break;
		}
		if (errno == ENOENT) {
			create_scorefile();
			od_kernel();
			continue;
		}
		if (errno != EACCES || wait_time + 10 <= time(NULL)) {
			break;
		}
		od_kernel();
	} while (!fptr);

	if (!fptr) {
		od_printf("\r\n\r\n`bright red`Error opening score file...\r\n");
		return;
	}

	for (i = 0; i < 10; i++) {
		fread(&hs[i], sizeof(struct high_scores), 1, fptr);
	}
	fclose(fptr);

	od_printf("`bright white`\r\n\r\nOregon Trail Top 10`white`\r\n");
	od_printf("---------------------------------------------------------\r\n");
	for (i = 0; i < 10; i++) {
		memcpy(&timetm, localtime(&hs[i].timestamp), sizeof(struct tm));
		od_printf("%2d. %-35s %-6d %02d/%02d/%4d\r\n", i + 1, hs[i].name, hs[i].score, timetm.tm_mon + 1, timetm.tm_mday, timetm.tm_year + 1900);
	}
	od_printf("---------------------------------------------------------\r\n");
	od_printf("Press any key to continue...\r\n");
	od_get_key(TRUE);
}

double rnd() {
	return (double)rand() / (double)RAND_MAX;
}

float shooting(int d9) {
	char *words[] = {
		"BANG",
		"BLAM",
		"POW",
		"WHAM"
	};
	char buffer[10];
	int s6 = rand() % 4;
	int b3, b1;
	od_printf("\r\nTYPE: %s\r\n", words[s6]);
	b3 = time(NULL);
	od_input_str(buffer, 10, 32, 127);
	b1 = time(NULL);
	b1 = (b1 - b3) - (d9 - 1);
	if (b1 > 0) {
		if (strcasecmp(buffer, words[s6]) == 0) {
			return b1;
		}
	}
	else {
		b1 = 0;
		if (strcasecmp(buffer, words[s6]) == 0) {
			return b1;
		}
	}
	return 9;
}

#if _MSC_VER
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
#else
int main(int argc, char **argv)
{
#endif

	int done = 0;
	char ch;
	char buffer[10];
	int d9;
	int t1;
	int dead;
	int score;
	int turn;
	float x1, k8, s4, f1, f2, m, m9, d3, a, f, b, c, m1, t, x, p, b1, e, s5, d1, r1, m2, f9;
	char *dates[] = {
		"MARCH 29",
		"APRIL 12",
		"APRIL 26",
		"MAY 10",
		"MAY 24",
		"JUNE 7",
		"JUNE 21",
		"JULY 5",
		"JULY 19",
		"AUGUST 2",
		"AUGUST 16",
		"AUGUST 31",
		"SEPTEMBER 13",
		"SEPTEMBER 27",
		"OCTOBER 11",
		"OCTOBER 25",
		"NOVEMBER 8",
		"NOVEMBER 22",
		"DECEMBER 6",
		"DECEMBER 20"
	};

#if _MSC_VER
	od_parse_cmd_line(lpszCmdLine);
#else
	od_parse_cmd_line(argc, argv);
#endif
	od_init();

	srand(time(NULL));

	od_send_file("intro.ans");

	od_printf("`white`Do you need instructions (Y / N) ? ");
	ch = od_get_answer("YyNn");
	od_printf("\r\n");
	if (tolower(ch) == 'y') {
		od_send_file("instructions.ans");
		od_get_key(TRUE);
	}

	while (!done) {
		od_printf("\r\n\r\n\r\n`white`What do you want to do?\r\n");
		od_printf("(`bright green`P`white`) Play Game\r\n");
		od_printf("(`bright green`S`white`) See High Scores\r\n");
		od_printf("(`bright green`I`white`) Show Instructions\r\n");
		od_printf("(`bright green`Q`white`) Quit\r\n");
		od_printf("? ");
		ch = od_get_key(TRUE);

		if (tolower(ch) == 'p') {
			od_printf("\r\n\r\nHow good a shot are you with your rifle?\r\n\r\n");
			od_printf(" (`bright green`1`white`) Ace Marksman, (`bright green`2`white`) Good Shot, (`bright green`3`white`) Fair to middlin\r\n");
			od_printf("    (`bright green`4`white`) Need more practice, (`bright green`5`white`) Shaky knees\r\n\r\n");
			od_printf("Enter one of the above - the better you claim you are, the\r\n");
			od_printf("faster you'll have to be with your gun to be successful.\r\n");
			od_printf("? ");
			od_input_str(buffer, 1, '1', '5');
			d9 = atoi(buffer);
			if (d9 > 9) {
				d9 = 0;
			}

			do {

				x1 = -1;
				k8 = 0;
				s4 = 0;
				f1 = 0;
				f2 = 0;
				m = 0;
				m9 = 0;
				d3 = 0;
				a = 0;
				f = 0;
				b = 0;
				c = 0;
				m1 = 0;
				dead = 0;
				m2 = 0;
				do {
					od_printf("\r\nHow much do you want to spend on your oxen team? ");
					od_input_str(buffer, 3, '0', '9');
					a = atoi(buffer);
					if (a < 200) {
						od_printf("\r\n\r\n`bright red`Not Enough!`white`\r\n\r\n");
						a = 0;
					}
					else if (a > 300) {
						od_printf("\r\n\r\n`bright red`Too Much!`white`\r\n\r\n");
						a = 0;
					}
				} while (a == 0);
				do {
					od_printf("\r\nHow much do you want to spend on food? ");
					od_input_str(buffer, 3, '0', '9');
					f = atoi(buffer);
					if (f < 0) {
						od_printf("\r\n\r\n`bright red`Impossible!`white`\r\n\r\n");
					}
				} while (f < 0);

				do {
					od_printf("\r\nHow much do you want to spend on ammunition? ");
					od_input_str(buffer, 3, '0', '9');
					b = atoi(buffer);
					if (b < 0) {
						od_printf("\r\n\r\n`bright red`Impossible!`white`\r\n\r\n");
					}
				} while (b < 0);

				do {
					od_printf("\r\nHow much do you want to spend on clothing? ");
					od_input_str(buffer, 3, '0', '9');
					c = atoi(buffer);
					if (c < 0) {
						od_printf("\r\n\r\n`bright red`Impossible!`white`\r\n\r\n");
					}
				} while (c < 0);

				do {
					od_printf("\r\nHow much do you want to spend on miscellaneous supplies? ");
					od_input_str(buffer, 3, '0', '9');
					m1 = atoi(buffer);
					if (m1 < 0) {
						od_printf("\r\n\r\n`bright red`Impossible!`white`\r\n\r\n");
					}
				} while (m1 < 0);
				t = 700 - a - f - b - c - m1;
				if (t < 0) {
					od_printf("\r\n\r\n`bright red`You overspent - you only had $700 to spend, buy again.`white`\r\n\r\n");
				}
			} while (t < 0);

			b = b * 50;

			od_printf("\r\n\r\nAfter all your purchases, you now have %d dollars left.\r\n\r\n", (int)t);

			for (d3 = 0; d3 < 20; d3++) {
				if (m >= 2040) {
					break;
				}
				od_printf("\r\n\r\n`bright white`MONDAY %s 1847`white`\r\n-------------------------------------------------------\r\n", dates[(int)floor(d3)]);
				f = floor(f);
				b = floor(b);
				c = floor(c);
				m1 = floor(m1);
				if (f < 0) f = 0;
				if (b < 0) b = 0;
				if (c < 0) c = 0;
				if (m1 < 0) m1 = 0;
				m2 = m;
				if (f < 13) {
					od_printf("`bright yellow`You'd better do some hunting or buy food and soon!!!`white`\r\n");
				}
				if (k8 == 1 || s4 == 1) {
					t = t - 20;
					if (t < 0) {
						od_printf("You can't afford a doctor!\r\n");
						od_printf("You died of ");
						if (k8 == 1) {
							od_printf("injuries\r\n");
						}
						else {
							od_printf("pneumonia\r\n");
						}
						dead = 1;
						break;
					}
					od_printf("The doctor's bill is $20\r\n");
					k8 = 0;
					s4 = 0;
				}
				if (m9 == 1) {
					od_printf("\r\nTotal mileage is 950\r\n");
					m9 = 0;
				}
				else {
					od_printf("\r\nTotal mileage is %d\r\n", (int)m);
				}

				od_printf("\r\n`bright white`FOOD        BULLETS     CLOTHING    MISC.SUPP.  CASH`white`\r\n");
				od_printf("%-11d %-11d %-11d %-11d %-11d\r\n", (int)f, (int)b, (int)c, (int)m1, (int)t);
				while (1) {
					if (x1 != -1) {
						od_printf("\r\nDo you want to \r\n   (`bright green`1`white`) Stop at the next fort, (`bright green`2`white`) Hunt, (`bright green`3`white`) Continue or (`bright green`Q`white`) Quit ? ");
						od_input_str(buffer, 1, 32, 126);
						if (tolower(buffer[0]) == 'q') {
							od_printf("Are you sure? (Y / N) ");
							ch = od_get_answer("yYnN");
							if (tolower(ch) == 'y') {
								od_exit(0, FALSE);
							}
							else {
								continue;
							}
						}
						x = atoi(buffer);
						if (x < 1 || x > 3) {
							x = 3;
						}

						if (x == 1) {
							// do fort
							od_printf("\r\nEnter what you wish to spend on the following...\r\n");

							do {
								od_printf("\r\nFOOD: ");
								od_input_str(buffer, 3, '0', '9');
								p = atoi(buffer);
								if (p > t) {
									od_printf("\r\nYou don't have that much -- keep your spending down\r\n");
								}
							} while (p > t);
							f = f + 0.6666 * p;
							t = t - p;
							do {
								od_printf("\r\nAMMUNITION: ");
								od_input_str(buffer, 3, '0', '9');
								p = atoi(buffer);
								if (p > t) {
									od_printf("\r\nYou don't have that much -- keep your spending down\r\n");
								}
							} while (p > t);
							b = b + (0.6666 * p) * 50;
							t = t - p;
							do {
								od_printf("\r\nCLOTHING: ");
								od_input_str(buffer, 3, '0', '9');
								p = atoi(buffer);
								if (p > t) {
									od_printf("\r\nYou don't have that much -- keep your spending down\r\n");
								}
							} while (p > t);
							c = c + 0.6666 * p;
							t = t - p;
							do {
								od_printf("\r\nMISCELLANEOUS SUPPLIES: ");
								od_input_str(buffer, 3, '0', '9');
								p = atoi(buffer);
								if (p > t) {
									od_printf("\r\nYou don't have that much -- keep your spending down\r\n");
								}
							} while (p > t);
							m1 = m1 + 0.6666 * p;
							t = t - p;
						}
					}
					else {
						od_printf("\r\nDo you want to (`bright green`1`white`) Hunt, (`bright green`2`white`) Continue, or (`bright green`Q`white`) Quit? ");
						od_input_str(buffer, 1, 32, 126);
						if (tolower(buffer[0]) == 'q') {
							od_printf("Are you sure? (Y / N) ");
							ch = od_get_answer("yYnN");
							if (tolower(ch) == 'y') {
								od_exit(0, FALSE);
							}
							else {
								continue;
							}
						}
						x = atoi(buffer);
						if (x < 1 || x > 2) {
							x = 2;
						}
						x = x + 1;
					}

					if (x == 2) {
						// hunt
						if (b > 39) {
							m = m - 45;
							b1 = shooting(d9);
							if (b1 <= 1) {
								od_printf("\r\nRight between the eyes --- you got a big one!!!\r\nFull bellies tonight\r\n");
								f = f + 52 + (rnd() * 6);
								b = b - 10 - rnd() * 4;
							}
							else {
								if (rnd() * 100 < 13 * b1) {
									od_printf("\r\nYou missed --- and your dinner got away...\r\n");
								}
								else {
									od_printf("\r\nNice shot --- right on target --- good eatin' tonight!!\r\n");
									f = f + 48 - 2 * b1;
									b = b - 10 - 3 * b1;
								}
							}
							break;
						}
						else {
							od_printf("\r\nTough -- you need more bullets to go hunting\r\n");
						}
					}
					if (x == 3) {
						// continue
						break;
					}
				}
				x1 = x1 * -1;

				if (f < 13) {
					od_printf("\r\nYou ran out of food and starved to death.\r\n");
					dead = 1;
					break;
				}

				while (1) {
					od_printf("\r\nDo you want to eat (`bright green`1`white`) poorly (`bright green`2`white`) moderately (`bright green`3`white`) well ?");
					od_input_str(buffer, 1, '1', '3');
					e = atoi(buffer);
					if (e > 3 || e < 1) {
						continue;
					}
					if (f - 8 - 5 * e < 0) {
						od_printf("\r\nYou can't eat that well.\r\n");
						continue;
					}
					f = f - 8 - 5 * e;
					break;
				}
				m = m + 200 + (1 - 220) / 5 + 10 * rnd();
				// riders
				if (rnd() * 10 <= (pow((m / 100 - 4), 27) + 72) / (pow((m / 100 - 4), 2) + 12) - 1) {
					od_printf("\r\nRiders ahead. They ");
					s5 = 0;
					if (rnd() < 0.8) {
						od_printf("look hostile.\r\n");
					}
					else {
						od_printf("don't look hostile.\r\n");
						s5 = 1;
					}

					while (1) {
						od_printf("\r\nTactics: (`bright green`1`white`) Run (`bright green`2`white`) Attack (`bright green`3`white`) Continue (`bright green`4`white`) Circle Wagons\r\n? ");
						if (rnd() < 0.2) {
							s5 = 1 - s5;
						}
						od_input_str(buffer, 1, '1', '4');
						t1 = atoi(buffer);
						if (t1 < 1 || t1 > 4) {
							continue;
						}
						break;
					}

					if (s5 == 1) {
						if (t1 == 1) {
							m = m + 15;
							a = a - 10;
						}
						else if (t1 == 2) {
							m = m - 5;
							b = b - 100;
						}
						else if (t1 == 4) {
							m = m - 20;
						}
						od_printf("\r\nRiders were friendly, but check for possible losses.\r\n");
					}
					else {
						if (t1 == 1) {
							m = m + 20;
							m1 = m1 - 15;
							b = b - 150;
							a = a - 40;
						}
						else if (t1 == 2) {
							b1 = shooting(d9);
							b = b - b1 * 40 - 80;
							if (b1 > 1) {
								if (b1 <= 4) {
									od_printf("\r\nKinda slow with with your colt .45\r\n");
								}
								else {
									od_printf("\r\nLousy shot --- you got knifed\r\n");
									k8 = 1;
									od_printf("You have to see ol' doc Blanchard\r\n");
								}
							}
							else {
								od_printf("\r\nNice shooting --- you drove them off\r\n");
							}

						}
						else if (t1 == 3) {
							if (rnd() > 0.8) {
								od_printf("\r\nThey did not attack\r\n");
							}
							else {
								b = b - 150;
								m1 = m1 - 15;
							}
						} else {
							b1 = shooting(d9);
							b = b - b1 * 30 - 80;
							m = m - 25;

							if (b1 > 1) {
								if (b1 <= 4) {
									od_printf("\r\nKinda slow with with your colt .45\r\n");
								}
								else {
									od_printf("\r\nLousy shot --- you got knifed\r\n");
									k8 = 1;
									od_printf("You have to see ol' doc Blanchard\r\n");
								}
							}
							else {
								od_printf("\r\nNice shooting --- you drove them off\r\n");
							}
						}

						od_printf("\r\nRiders were hostile -- check for losses.\r\n");
						if (b < 0) {
							od_printf("\r\nYou ran out of bullets and got massacred by the riders.\r\n");
							dead = 1;
							break;
						}
					}
				}
				// selection of events
				d1 = 0;
				r1 = rnd() * 100;
				if (r1 < 6) {
					od_printf("\r\nWagon breaks down -- lose time and supplies fixing it\r\n");
					m = m - 16 - 5 * rnd();
					m1 = m1 - 8;
				}
				else if (r1 < 11) {
					od_printf("\r\nOx injures leg -- slows you down rest of trip\r\n");
					m = m - 25;
					a = a - 20;
				}
				else if (r1 < 13) {
					od_printf("\r\nBad luck -- Your daughter broke her arm\r\nYou had to stop and use supplies to make a sling\r\n");
					m = m - 5 - 4 * rnd();
					m1 = m1 - 2 - 3 * rnd();
				}
				else if (r1 < 15) {
					od_printf("\r\nOx wanders off -- Spend time looking for it.\r\n");
					m = m - 17;
				}
				else if (r1 < 17) {
					od_printf("\r\nYour son gets lost -- spend half the day looking for him.\r\n");
					m = m - 10;
				}
				else if (r1 < 22) {
					od_printf("\r\nUnsafe water -- lose time looking for clean spring.\r\n");
					m = m - 10 * rnd() * -2;
				}
				else if (r1 < 32) {
					if (m > 950) {
						od_printf("\r\nCold weather --- brrrrrrr! --- You ");
						if (c > 22 + 4 * rnd()) {
							od_printf("have enough clothing to keep warm.\r\n");
						}
						else {
							od_printf("don't have enough clothing to keep warm.\r\n");
							// illness subroutine
							if (100 * rnd() < 10 + 35 * (e - 1)) {
								od_printf("Mild Illness -- Medicine used\r\n");
								m = m - 5;
								m1 = m1 - 2;
								if (m1 < 0) {
									od_printf("\r\nYou ran out of medical supplies. You died of pneumonia.\r\n");
									dead = 1;
									break;
								}
							}
							else if (100 * rnd() < 100 - 40 / pow(4, e - 1)) {
								od_printf("Bad Illness -- Medicine used\r\n");
								m = m - 5;
								m1 = m1 - 2;
								if (m1 < 0) {
									od_printf("\r\nYou ran out of medical supplies. You died of pneumonia.\r\n");
									dead = 1;
									break;
								}
							}
							else {
								od_printf("Serious Illness -- You must stop for medical attention.\r\n");
								m1 = m1 - 10;
								s4 = 1;
								if (m1 < 0) {
									od_printf("\r\nYou ran out of medical supplies. You died of pneumonia.\r\n");
									dead = 1;
									break;
								}
							}
						}
					}
					else {
						od_printf("\r\nHeavy rains -- Time and supplies lost.\r\n");
						f = f - 10;
						b = b - 500;
						m1 = m1 - 15;
						m = m - 10 * rnd() - 5;
					}
				}
				else if (r1 < 35) {
					od_printf("\r\nBandits attack\r\n");
					b1 = shooting(d9);
					b = b - 20 * b1;
					if (b < 0) {
						od_printf("\r\nYou ran out of bullets --- they get lots of cash\r\n");
						t = t / 3;
						od_printf("You got shot in the leg and they took one of your oxen\r\n");
						k8 = 1;
						od_printf("Better have a doc look at your wound\r\n");
						m1 = m1 - 5;
						a = a - 20;
					}
					else if (b1 <= 1) {
						od_printf("\r\nQuickest draw outside of dodge city!!!!\r\nYou got 'em!\r\n");
					}
					else {
						od_printf("You got shot in the leg and they took one of your oxen\r\n");
						k8 = 1;
						od_printf("Better have a doc look at your wound\r\n");
						m1 = m1 - 5;
						a = a - 20;
					}
				}
				else if (r1 < 37) {
					od_printf("\r\nThere was a fire in your wagon -- food and supplies damaged!\r\n");
					f = f - 40;
					b = b - 400;
					m1 = m1 - rnd() * 68 - 3;
					m = m - 15;
				}
				else if (r1 < 42) {
					od_printf("\r\nLose your way in heavy fog --- time is lost\r\n");
					m = m - 10 - 5 * rnd();
				}
				else if (r1 < 44) {
					od_printf("\r\nYou killed a poisonous snake after it bit you\r\n");
					b = b - 10;
					m1 = m1 - 5;
					if (m1 < 0) {
						od_printf("\r\nYou die of snakebite since you have no medicine\r\n");
						dead = 1;
						break;
					}
				}
				else if (r1 < 54) {
					od_printf("\r\nYour wagon gets swamped fording river -- lose food and clothes\r\n");
					f = f - 30;
					c = c - 20;
					m = m - 20 - 20 * rnd();
				}
				else if (r1 < 64) {
					od_printf("\r\nWild animals attack!\r\n");
					b1 = shooting(d9);
					if (b <= 39) {
						od_printf("\r\nYou were too low on bullets -- the wolves overpowered you\r\n");
						k8 = 1;
						dead = 1;
						od_printf("\r\nYou ran out of medical supplies. You died of injuries.\r\n");
						break;
					}
					if (b1 <= 2) {
						od_printf("\r\nNice shootin' pardner -- they didn't get much\r\n");
					}
					else {
						od_printf("\r\nSlow on the draw --- they got at your food and clothes\r\n");
					}
					b = b - 20 * b1;
					c = c - b1 * 4;
					f = f - b1 * 8;
				}
				else if (r1 < 69) {
					od_printf("\r\nHail storm --- supplies damaged\r\n");
					m = m - 5 - rnd() * 10;
					b = b - 200;
					m1 = m1 - 4 - rnd() * 3;
				}
				else if (r1 < 95) {
					if (e == 1) {
						// illness sub
						if (100 * rnd() < 10 + 35 * (e - 1)) {
							od_printf("Mild Illness -- Medicine used\r\n");
							m = m - 5;
							m1 = m1 - 2;
							if (m1 < 0) {
								dead = 1;
								od_printf("\r\nYou ran out of medical supplies. You died of pneumonia.\r\n");
								break;
							}
						}
						else if (100 * rnd() < 100 - 40 / pow(4, e - 1)) {
							od_printf("Bad Illness -- Medicine used\r\n");
							m = m - 5;
							m1 = m1 - 2;
							if (m1 < 0) {
								dead = 1;
								od_printf("\r\nYou ran out of medical supplies. You died of pneumonia.\r\n");
								break;
							}
						}
						else {
							od_printf("Serious Illness -- You must stop for medical attention.\r\n");
							m1 = m1 - 10;
							s4 = 1;
							if (m1 < 0) {
								dead = 1;
								od_printf("\r\nYou ran out of medical supplies. You died of pneumonia.\r\n");
								break;
							}
						}
					}
					else if (e == 2) {
						if (rnd() > 0.25) {
							// illness sub
							if (100 * rnd() < 10 + 35 * (e - 1)) {
								od_printf("Mild Illness -- Medicine used\r\n");
								m = m - 5;
								m1 = m1 - 2;
								if (m1 < 0) {
									dead = 1;
									od_printf("\r\nYou ran out of medical supplies. You died of pneumonia.\r\n");
									break;
								}
							}
							else if (100 * rnd() < 100 - 40 / pow(4, e - 1)) {
								od_printf("Bad Illness -- Medicine used\r\n");
								m = m - 5;
								m1 = m1 - 2;
								if (m1 < 0) {
									dead = 1;
									od_printf("\r\nYou ran out of medical supplies. You died of pneumonia.\r\n");
									break;
								}
							}
							else {
								od_printf("Serious Illness -- You must stop for medical attention.\r\n");
								m1 = m1 - 10;
								s4 = 1;
								if (m1 < 0) {
									dead = 1;
									od_printf("\r\nYou ran out of medical supplies. You died of pneumonia.\r\n");
									break;
								}
							}
						}
					}
					else if (e == 3) {
						if (rnd() < 0.5) {
							// illness sub
							if (100 * rnd() < 10 + 35 * (e - 1)) {
								od_printf("Mild Illness -- Medicine used\r\n");
								m = m - 5;
								m1 = m1 - 2;
								if (m1 < 0) {
									dead = 1;
									od_printf("\r\nYou ran out of medical supplies. You died of pneumonia.\r\n");
									break;
								}
							}
							else if (100 * rnd() < 100 - 40 / pow(4, e - 1)) {
								od_printf("Bad Illness -- Medicine used\r\n");
								m = m - 5;
								m1 = m1 - 2;
								if (m1 < 0) {
									dead = 1;
									od_printf("\r\nYou ran out of medical supplies. You died of pneumonia.\r\n");
									break;
								}
							}
							else {
								od_printf("Serious Illness -- You must stop for medical attention.\r\n");
								m1 = m1 - 10;
								s4 = 1;
								if (m1 < 0) {
									dead = 1;
									od_printf("\r\nYou ran out of medical supplies. You died of pneumonia.\r\n");
									break;
								}
							}
						}
					}
				}
				else {
					od_printf("\r\nHelpful indians show you where to find more food\r\n");
					f = f + 14;
				}
				if (m <= 950) {
					continue;
				}
				if (rnd() * 10 <= 9 - (pow(m / 100 - 15, 2) + 72) / (pow(m / 100 - 15, 2) + 12)) {
					od_printf("\r\nRugged mountains\r\n");
					if (rnd() < 0.1) {
						od_printf("You got lost -- lose valuable time trying to find trail!\r\n");
						m = m - 60;
					}
					else if (rnd() < 0.11) {
						od_printf("Wagon damaged! -- Lose time and supplies\r\n");
						m1 = m1 - 5;
						b = b - 200;
						m = m - 20 - 30 * rnd();
					}
					else {
						od_printf("The going gets slow\r\n");
						m = m - 45 - rnd() / 0.02;
					}
				}
				if (f1 != 1) {
					f1 = 1;
					if (rnd() < 0.8) {
						od_printf("\r\nBlizzard in mountain pass --- time and supplies lost\r\n");
						f = f - 25;
						m1 = m1 - 10;
						b = b - 300;
						m = m - 30 - 40 * rnd();
						if (c < 18 + 2 * rnd()) {
							if (100 * rnd() < 10 + 35 * (e - 1)) {
								od_printf("Mild Illness -- Medicine used\r\n");
								m = m - 5;
								m1 = m1 - 2;
								if (m1 < 0) {
									dead = 1;
									od_printf("\r\nYou ran out of medical supplies. You died of pneumonia.\r\n");
									break;
								}
							}
							else if (100 * rnd() < 100 - 40 / pow(4, e - 1)) {
								od_printf("Bad Illness -- Medicine used\r\n");
								m = m - 5;
								m1 = m1 - 2;
								if (m1 < 0) {
									dead = 1;
									od_printf("\r\nYou ran out of medical supplies. You died of pneumonia.\r\n");
									break;
								}
							}
							else {
								od_printf("Serious Illness -- You must stop for medical attention.\r\n");
								m1 = m1 - 10;
								s4 = 1;
								if (m1 < 0) {
									dead = 1;
									od_printf("\r\nYou ran out of medical supplies. You died of pneumonia.\r\n");
									break;
								}
							}
						}
						if (m > 950) {
							continue;
						}
						m9 = 1;
						continue;
					}
					else {
						od_printf("\r\nYou made it safely through the south pass -- no snow\r\n");
						if (m < 1700) {
							if (m > 950) {
								continue;
							}
							m9 = 1;
							continue;
						}
						if (f2 == 1) {
							if (m > 950) {
								continue;
							}
							m9 = 1;
							continue;
						}
						f2 = 1;
						if (rnd() < 0.7) {
							od_printf("\r\nBlizzard in mountain pass --- time and supplies lost\r\n");
							f = f - 25;
							m1 = m1 - 10;
							b = b - 300;
							m = m - 30 - 40 * rnd();
							if (c < 18 + 2 * rnd()) {
								if (100 * rnd() < 10 + 35 * (e - 1)) {
									od_printf("Mild Illness -- Medicine used\r\n");
									m = m - 5;
									m1 = m1 - 2;
									if (m1 < 0) {
										dead = 1;
										od_printf("\r\nYou ran out of medical supplies. You died of pneumonia.\r\n");
										break;
									}
								}
								else if (100 * rnd() < 100 - 40 / pow(4, e - 1)) {
									od_printf("Bad Illness -- Medicine used\r\n");
									m = m - 5;
									m1 = m1 - 2;
									if (m1 < 0) {
										dead = 1;
										od_printf("\r\nYou ran out of medical supplies. You died of pneumonia.\r\n");
										break;
									}
								}
								else {
									od_printf("Serious Illness -- You must stop for medical attention.\r\n");
									m1 = m1 - 10;
									s4 = 1;
									if (m1 < 0) {
										dead = 1;
										od_printf("\r\nYou ran out of medical supplies. You died of pneumonia.\r\n");
										break;
									}
								}
							}
							if (m > 950) {
								continue;
							}
							m9 = 1;
							continue;
						}
					}
				}
				else {
					od_printf("\r\nYou made it safely through the south pass -- no snow\r\n");
					if (m < 1700) {
						if (m > 950) {
							continue;
						}
						m9 = 1;
						continue;
					}
					if (f2 == 1) {
						if (m > 950) {
							continue;
						}
						m9 = 1;
						continue;
					}
					f2 = 1;
					if (rnd() < 0.7) {
						od_printf("\r\nBlizzard in mountain pass --- time and supplies lost\r\n");
						f = f - 25;
						m1 = m1 - 10;
						b = b - 300;
						m = m - 30 - 40 * rnd();
						if (c < 18 + 2 * rnd()) {
							if (100 * rnd() < 10 + 35 * (e - 1)) {
								od_printf("Mild Illness -- Medicine used\r\n");
								m = m - 5;
								m1 = m1 - 2;
								if (m1 < 0) {
									dead = 1;
									od_printf("\r\nYou ran out of medical supplies. You died of pneumonia.\r\n");
									break;
								}
							}
							else if (100 * rnd() < 100 - 40 / pow(4, e - 1)) {
								od_printf("Bad Illness -- Medicine used\r\n");
								m = m - 5;
								m1 = m1 - 2;
								if (m1 < 0) {
									dead = 1;
									od_printf("\r\nYou ran out of medical supplies. You died of pneumonia.\r\n");
									break;
								}
							}
							else {
								od_printf("Serious Illness -- You must stop for medical attention.\r\n");
								m1 = m1 - 10;
								s4 = 1;
								if (m1 < 0) {
									dead = 1;
									od_printf("\r\nYou ran out of medical supplies. You died of pneumonia.\r\n");
									break;
								}
							}
						}
						if (m > 950) {
							continue;
						}
						m9 = 1;
						continue;
					}
				}
			}
			if (dead || d3 == 20) {
				if (d3 == 20) {
					od_printf("\r\nYou have been on the trail too long -----\r\n");
					od_printf("Your family dies in the first blizzard of winter\r\n");
				}
				od_printf("\r\nDue to your unfortunate situation, there are a few\r\n");
				od_printf("formalities we must go through.\r\n");
				od_printf("\r\nWould you like a minister? ");
				od_get_answer("YyNn");
				od_printf("\r\nWould you like a fancy funeral? ");
				od_get_answer("YyNn");
				od_printf("\r\nWould you like to inform your next of kin? ");
				ch = od_get_answer("YyNn");
				if (tolower(ch) == 'n') {
					od_printf("\r\n...but your aunt sadie in St. Louis is really worried about you.\r\n");
				}
				else {
					od_printf("\r\n...that will be $4.50 for the telegraph charge\r\n");
				}

				od_printf("\r\nWe thank you for this information and we are sorry you\r\n");
				od_printf("didn't make it to the great territory of Oregon.\r\n");
				od_printf("Better luck next time.\r\n\r\n\r\n");
				od_printf("                              Sincerley\r\n");
				od_printf("                             The Oregon city Chamber of Commerce\r\n");

			}
			else {
				turn = d3;
				f9 = (2040 - m2) / (m - m2);
				f = f + (1 - f9) * (8 + 5 * e);
				od_printf("\r\n\r\nYou finally arrived at oregon city\r\n");
				od_printf("after 2040 long miles --- hooray!!!!\r\n");
				od_printf("A real pioneer!\r\n\r\n");
				f9 = f9 * 14;
				d3 = d3 * 14 + f9;
				f9 = f9 + 1;
				if (f9 >= 7) {
					f9 = f9 - 7;
				}
				switch ((int)floor(f9)) {
				case 0:
					od_printf("Monday ");
					break;

				case 1:
					od_printf("Tuesday ");
					break;

				case 2:
					od_printf("Wednesday ");
					break;

				case 4:
					od_printf("Thursday ");
					break;

				case 5:
					od_printf("Friday ");
					break;

				case 6:
					od_printf("Saturday ");
					break;

				case 7:
					od_printf("Sunday ");
					break;
				}
				if (d3 <= 124) {
					d3 = d3 - 93;
					od_printf("July %d 1847\r\n", (int)d3);
				}
				else if (d3 <= 155) {
					d3 = d3 - 124;
					od_printf("August %d 1847\r\n", (int)d3);
				}
				else if (d3 <= 165) {
					d3 = d3 - 155;
					od_printf("September %d 1847\r\n", (int)d3);
				}
				else if (d3 <= 216) {
					d3 = d3 - 165;
					od_printf("October %d 1847\r\n", (int)d3);
				}
				else if (d3 <= 246) {
					d3 = d3 - 216;
					od_printf("November %d 1847\r\n", (int)d3);
				}
				else {
					d3 = d3 - 256;
					od_printf("December %d 1847\r\n", (int)d3);
				}
				od_printf("\r\n`bright white`FOOD        BULLETS     CLOTHING    MISC.SUPP.  CASH`white`\r\n");
				if (f < 0) f = 0;
				if (b < 0) b = 0;
				if (c < 0) c = 0;
				if (m1 < 0) m1 = 0;
				if (t < 0) t = 0;
				od_printf("%-11d %-11d %-11d %-11d %-11d\r\n", (int)f, (int)b, (int)c, (int)m1, (int)t);
				od_printf("\r\nPresident James K. Polk sends you his heartiest congratulations\r\n");
				od_printf("and wishes you a prosperous life ahead at your new home.\r\n");

				score = (int)f + (int)(b / 50) + (int)c + (int)m1 + (int)t;
				score = score * (22 - turn) * (6 - d9);

				if (add_highscore(score)) {
					od_printf("\r\n`bright green`You got a high score!`white`\r\n");
				}

				od_printf("\r\nPress any key to continue\r\n");
				od_get_key(TRUE);
			}

		}
		else if (tolower(ch) == 's') {
			show_highscores();
		}
		else if (tolower(ch) == 'i') {
			od_send_file("instructions.ans");
			od_get_key(TRUE);
		}
		else if (tolower(ch) == 'q') {
			done = 1;
		}
	}

	od_exit(0, FALSE);
}
