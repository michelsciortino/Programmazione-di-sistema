#include "stdafx.h"
#include "StringBuffer.h"
#include <string.h>
#include <stdexcpt.h>

#define MIN 80

StringBuffer::StringBuffer(void)
{
	this->buffer = new char[MIN];
	this->_buff_size = MIN;
	this->_size = 0;
}

StringBuffer::StringBuffer(const char *str)
{
	if(str == NULL)
		throw std::exception("null item exception");
	this->_size = strlen(str)+1;
	this->_buff_size = this->_size * 2;
	this->buffer = new char[this->_buff_size];
	memcpy(this->buffer, str, this->_size);
}

StringBuffer::StringBuffer(const StringBuffer& sb)
{
	this->_size = sb._size;
	this->_buff_size = sb._size * 2;
	this->buffer = new char[this->_buff_size];
	memcpy(this->buffer, sb.buffer, sb._size);
}

StringBuffer::~StringBuffer(){
	delete[] this->buffer;
	buffer = NULL;	
}

size_t StringBuffer::size()
{
	return this->_size;
}

size_t StringBuffer::bufsize()
{
	return this->_buff_size;
}

void StringBuffer::clear()
{
	this->_size = 0;
}

void StringBuffer::insert(const char* str, size_t pos)
{
	if (str == NULL)
		throw std::exception("null item exception");
	int oldsize = this->_size;
	if (pos + strlen(str)> _buff_size)
	{
		char *tmp = new char[this->_size];
		memcpy(tmp, this->buffer, this->_size);
		delete[] this->buffer;
		this->_size = pos + strlen(str) + 1;
		this->_buff_size = this->_size * 2;
		this->buffer = new char[this->_buff_size];
		memcpy(buffer, tmp, oldsize - 1);
		delete[] tmp;
		tmp = NULL;
	}
	for (int i = oldsize - 1; i < pos; i++)
		this->buffer[i] = ' ';
	if (pos + strlen(str) < oldsize)
		memcpy(this->buffer + pos, str, strlen(str));
	else
		memcpy(this->buffer + pos, str, strlen(str) + 1);
}

void StringBuffer::insert(const StringBuffer& sb, size_t pos)
{
	int oldsize = this->_size;
	if (pos + sb._size> _buff_size)
	{
		char *tmp = new char[this->_size];
		memcpy(tmp, this->buffer, this->_size);
		delete[] this->buffer;
		this->_size = pos + sb._size + 1;
		this->_buff_size = this->_size * 2;
		this->buffer = new char[this->_buff_size];
		memcpy(buffer, tmp, oldsize);
		delete[] tmp;
		tmp = NULL;
	}
	for (int i = oldsize; i < pos; i++)
		this->buffer[i] = ' ';
	if (pos + sb._size< oldsize)
		memcpy(this->buffer + pos, sb.buffer, sb._size);
	else
		memcpy(this->buffer + pos, sb.buffer, sb._size);
	this->_size = oldsize + sb._size-1;
	
}

void StringBuffer::append(const char* str)
{
	if (str == NULL)
		throw std::exception("null item exception");
	if (this->_size + strlen(str)+1 > this->_buff_size) {
		char* tmp = new char[this->_size];
		memcpy(tmp, this->buffer, this->_size);
		delete[] this->buffer;
		this->_buff_size = (this->_size + strlen(str)) * 2;
		this->buffer = new char[this->_buff_size];
		memcpy(buffer, tmp, this->_size - 1);
		delete[] tmp;
		tmp = NULL;
	}
	memcpy(buffer + this->_size-1, str, strlen(str)+1);
	this->_size = this->_size + strlen(str);
}

void StringBuffer::append(const StringBuffer& sb)
{
	if (this->_size + sb._size> this->_buff_size) {
		char* tmp = new char[this->_size];
		memcpy(tmp, this->buffer, this->_size);
		delete[] this->buffer;
		this->_buff_size = (this->_size + strlen(sb.buffer)) * 2;
		this->buffer = new char[this->_buff_size];
		memcpy(buffer, tmp, this->_size - 1);
		delete[] tmp;
		tmp = NULL;
	}
	memcpy(buffer + this->_size - 1, sb.buffer, sb._size);
}

const char* StringBuffer::c_str()
{
	return this->buffer;
}

void StringBuffer::set(const char* str)
{
	if (str == NULL)
		throw std::exception("null item exception");
	if (strlen(str) > this->_buff_size) {
		delete[] buffer;
		this->_buff_size = strlen(str) * 2;
		buffer = new char[this->_buff_size];
	}
	memcpy(this->buffer, str, strlen(str)+1);
	this->_size = strlen(str) + 1;
}

void StringBuffer::set(const StringBuffer& s)
{
	if (s._size > this->_buff_size) {
		delete[] buffer;
		this->_buff_size = s._size * 2;
		buffer = new char[this->_buff_size];
	}
	memcpy(this->buffer, s.buffer, s._size);
	this->_size = s._size;
}