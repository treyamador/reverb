#include "reader_writer.h"
#include "wav.h"


namespace {
	const int TAG_SIZE = 4;
}


ReaderWriter::ReaderWriter() {}


ReaderWriter::~ReaderWriter() {}


WAV* ReaderWriter::read(const std::string& filepath) {

	FILE* file_ptr = nullptr;
	if ((file_ptr = fopen(filepath.c_str(), "rb")) == nullptr)
		return error_message_pointer("could not open wav file");

	WAV* wav = new WAV;

	fread(wav->header_->riff_tag_, sizeof(char), 4, file_ptr);
	fread(wav->header_->riff_length_, sizeof(int), 1, file_ptr);
	fread(wav->header_->wav_tag_, sizeof(char), 4, file_ptr);
	fread(wav->header_->fmt_tag_, sizeof(char), 4, file_ptr);
	fread(wav->header_->fmt_length_, sizeof(int), 1, file_ptr);
	fread(wav->header_->audio_format_, sizeof(short), 1, file_ptr);
	fread(wav->header_->num_channels_, sizeof(short), 1, file_ptr);
	fread(wav->header_->sample_rate_, sizeof(int), 1, file_ptr);
	fread(wav->header_->byte_rate_, sizeof(int), 1, file_ptr);
	fread(wav->header_->block_align_, sizeof(short), 1, file_ptr);
	fread(wav->header_->bits_per_sample_, sizeof(short), 1, file_ptr);
	fread(wav->header_->data_tag_, sizeof(int), 4, file_ptr);
	fread(wav->header_->data_length_, sizeof(int), 1, file_ptr);

	int buf_len = *wav->header_->data_length_;
	wav->body_->data_ = new char[buf_len + 1];
	wav->body_->data_[buf_len] = '\0';
	fread(wav->body_->data_, sizeof(char), buf_len, file_ptr);
	fflush(file_ptr);
	fclose(file_ptr);

	return wav;
}


void ReaderWriter::write(WAV* wav, const std::string& filepath) {

	FILE* file_ptr = nullptr;
	if ((file_ptr = fopen(filepath.c_str(), "wb")) == nullptr) {
		error_message_bool("could not open write file");
		return;
	}

	fwrite(wav->header_->riff_tag_, sizeof(char), 4, file_ptr);
	fwrite(wav->header_->riff_length_, sizeof(int), 1, file_ptr);
	fwrite(wav->header_->wav_tag_, sizeof(char), 4, file_ptr);
	fwrite(wav->header_->fmt_tag_, sizeof(char), 4, file_ptr);
	fwrite(wav->header_->fmt_length_, sizeof(int), 1, file_ptr);
	fwrite(wav->header_->audio_format_, sizeof(short), 1, file_ptr);
	fwrite(wav->header_->num_channels_, sizeof(short), 1, file_ptr);
	fwrite(wav->header_->sample_rate_, sizeof(int), 1, file_ptr);
	fwrite(wav->header_->byte_rate_, sizeof(int), 1, file_ptr);
	fwrite(wav->header_->block_align_, sizeof(short), 1, file_ptr);
	fwrite(wav->header_->bits_per_sample_, sizeof(short), 1, file_ptr);
	fwrite(wav->header_->data_tag_, sizeof(char), 4, file_ptr);
	fwrite(wav->header_->data_length_, sizeof(int), 1, file_ptr);

	fwrite(wav->body_->data_, sizeof(char), *wav->header_->data_length_, file_ptr);
	fflush(file_ptr);
	fclose(file_ptr);
}


// revise this?
// place this in wav_manager?
bool ReaderWriter::error_check(WAV* wav) {
	return true;
}


bool ReaderWriter::error_message_bool(const std::string& message) {
	std::cout << "Error: " << message << std::endl;
	return false;
}


WAV* ReaderWriter::error_message_pointer(const std::string& message) {
	std::cout << "Error: " << message << std::endl;
	return nullptr;
}

