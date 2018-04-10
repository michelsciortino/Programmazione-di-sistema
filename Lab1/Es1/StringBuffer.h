#pragma once
class StringBuffer
{
public:

	/*Costruisce un oggetto con un buffer di dimensione iniziale ragionevole e 0
	caratteri utilizzati*/
	StringBuffer(void);

	/*Costruisce un oggetto allocando un buffer di dimensione sufficiente a contenere l’array
	di caratteri str (compreso il terminatore finale) e segnando correttamente il numero
	di caratteri effettivamente utilizzati*/
	StringBuffer(const char *str);

	/*Costruisce un oggetto con un buffer iniziale di dimensione adeguata a contenere i caratteri
	contenuti nell’oggetto sb e inizializzato con una copia di tali caratteri*/
	StringBuffer(const StringBuffer& sb);

	/*Rilascia le risorse contenute nell’oggetto*/
	~StringBuffer();

	/*Restituisce il numero di caratteri utilizzati dalla stringa memorizzata nel buffer*/
	size_t size();

	/*Restituisce la dimensione totale del buffer di caratteri*/
	size_t bufsize();

	/*Porta a 0 il numero di caratteri utilizzati*/
	void clear();

	/*Inserisce il contenuto s nella posizione pos del buffer*/
	void insert(const char* str, size_t pos);

	/*Inserisce il contenuto di sb nella posizione pos del buffer*/
	void insert(const StringBuffer& sb, size_t pos);

	/*aggiunge i caratteri contenuti in str in coda a quelli memorizzati nel buffer, riallocando il buffer se necessario*/
	void append(const char* str);

	/*Aggiunge i caratteri contenuti nell’oggetto sb in coda a quelli memorizzati nel buffer, riallocando il buffer se necessario*/
	void append(const StringBuffer& sb);

	/*Restituisce un puntatore in sola lettura al buffer interno opportunamente terminato con un "\0"*/
	const char* c_str();

	/*Sostituisce la stringa memorizzata nel buffer con il contenuto dell’array s, riallocando il buffer se necessario*/
	void set(const char* str);

	/*Sostituisce la stringa memorizzata nel buffer con il contenuto dell’oggetto s, riallocando il buffer se necessario*/
	void set(const StringBuffer& s);

private:
	/*char buffer*/
	char *buffer;
	/*content size*/
	int _size;
	/*buffer size*/
	int _buff_size;
};