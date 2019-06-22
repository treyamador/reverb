#ifndef READER_WRTIER_H_
#define READER_WRITER_H_
#include <string>
struct WAV;


class ReaderWriter {

public:
	ReaderWriter();
	~ReaderWriter();

	WAV* read(const std::string& filepath);
	void write(WAV* wav, const std::string& filepath);

	bool error_check(WAV* wav);


private:
	WAV* error_message_pointer(const std::string& message);
	bool error_message_bool(const std::string& message);


};


#endif
