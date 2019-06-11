#include "../include/Message.hpp"

void DevsMessage::MakeContent(std::string P, std::string V){
	Port = P;
	Value = V;
}

std::string DevsMessage::ContentPort() {
	return Port;
}

std::string DevsMessage::ContentValue() {
	return Value;
}

/**
 * GenericMessage
 *
 * Supported types: std::string, double
 */
void GenericMessage<std::string>::MakeContent(std::string port, std::string value) {
	this->port = port;
	this->value = value;
}

void GenericMessage<double>::MakeContent(std::string port, double value) {
	this->port = port;
	this->value = value;
}