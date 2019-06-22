#ifndef WAV_MANAGER_H_
#define WAV_MANAGER_H_
#include <string>
#include <memory>
#include <vector>
#include <map>
class ReaderWriter;
struct WAV;


class WAVManager {

public:
	WAVManager();
	~WAVManager();

	WAV* add_wav(const std::string& filepath);
	void write_wav(WAV* wav, const std::string& filepath);

	void delete_wav(const std::string& key);
	void clear_wav_files();

	WAV* create_empty_given_format(WAV* prototype);
	WAV* create_sized_given_format(WAV* prototype, int size);
	void set_size(WAV* unsized_wav, int size);

	int largest_data_size(std::vector<WAV*>& channels);
	void copy_tag(char*& dest, char* source);

	WAV* operator[](int k);
	WAV* operator[](const std::string& key);
	std::vector<std::string> query_keys();
	size_t size();


private:
	std::shared_ptr<ReaderWriter> reader_writer_;
	std::map<std::string, WAV*> wav_files_;


};


#endif
