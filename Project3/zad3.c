#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define _CRT_SECURE_NO_WARNINGS
#define MAX 50

typedef struct osoba* Pozicija;

struct osoba {
	char ime[MAX];
	char prezime[MAX];
	int god;
	Pozicija next;
}_os;

Pozicija novaOsoba();
void ispis(Pozicija);
void unosPocetak(Pozicija, Pozicija);
void unosKraj(Pozicija, Pozicija);
Pozicija pronadji(Pozicija, char[MAX]);
void izbrisi(Pozicija, char[MAX]);

int main() {

	Pozicija head, p, trazen;
	head = p = trazen = NULL;
	char op = ' ';
	char pom[MAX] = " ";

	printf("Opcije:\nNova osoba na pocetak - P\nNova osoba na kraj - K\nIspis - I\nPretraga - S\nIzbrisi - B\nIzadji - E\n");
	while (1) {
		printf("Unesite sto zelite.\n");

		scanf(" %c", &op);
		op = toupper(op);
		switch (op) {

		case 'P':
			p = novaOsoba();
			unosPocetak(&head, p);
			printf("Unos na pocetak obavljen.\n");
			break;

		case 'K':
			p = novaOsoba();
			unosKraj(&head, p);
			printf("Unos na kraj obavljen.\n");
			break;

		case 'I':
			ispis(&head);
			break;

		case 'S':
			printf("Unesite prezime trazene osobe:\n");
			scanf("%s", pom);
			trazen = pronadji(&head, pom);
			if (trazen == NULL)
				printf("\nGreska, te osobe nema.\n");
			else
				printf("%s %s %d\n", trazen->ime, trazen->prezime, trazen->god);
			break;

		case 'B':
			printf("Unesite ime osobe koju zelite izbrisati:\n");
			scanf("%s", pom);
			izbrisi(&head, pom);
			printf("Osoba (%s) uspijesno izbrisana.\n", pom);
			break;

		case 'E':
			return 0;
			break;

		default:
			printf("Greska; upisite jedno od gore zadanih slova.");
			break;

		}
	}
	return 0;
}

Pozicija novaOsoba() {

	Pozicija p;

	p = (Pozicija)malloc(sizeof(struct osoba));
	printf("Unesite ime, prezime i godinu rodjenja:\n");
	scanf(" %s %s %d", &p->ime, &p->prezime, &p->god);
	p->next = NULL;
	return p;
}


void unosPocetak(Pozicija head, Pozicija p) {

	p->next = head->next;
	head->next = p;
}

void unosKraj(Pozicija q, Pozicija p) {


	while (q->next != NULL) {
		q = q->next;
	}
	unosPocetak(q, p);
}

Pozicija pronadji(Pozicija q, char prez[MAX]) {

	while (q->next != NULL && strcmp(q->prezime, prez))
		q = q->next;

	return q;
}

void izbrisi(Pozicija p, char ime[MAX]) {
	Pozicija prev;
	prev = p;
	p = p->next;

	while (p->next != NULL && strcmp(p->ime, ime)) {
		prev = p;
		p = p->next;
	}

	if (prev != NULL) {
		p = prev->next;
		prev->next = p->next;
		free(p);
	}
}

void ispis(Pozicija p) {

	p = p->next;

	printf("---------------------------\n");
	while (p != NULL) {
		printf("%s %s, %d\n", p->ime, p->prezime, p->god);
		p = p->next;
	}
}
