#include "ToDo_Service.hpp"
#include <random>
#include <sstream>
#include <thread>


ToDo_Service::ToDo_Service()
{
	// TODO: Logic here
}

std::string ToDo_Service::generate_id() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 15);
	std::uniform_int_distribution<> dis2(8, 11);
	std::stringstream ss;
	int i;
	ss << std::hex;
	for (i = 0; i < 8; i++) {
		ss << dis(gen);
	}
	ss << "-";
	for (i = 0; i < 4; i++) {
		ss << dis(gen);
	}
	ss << "-4";
	for (i = 0; i < 3; i++) {
		ss << dis(gen);
	}
	ss << "-";
	ss << dis2(gen);
	for (i = 0; i < 3; i++) {
		ss << dis(gen);
	}
	ss << "-";
	for (i = 0; i < 12; i++) {
		ss << dis(gen);
	};
	return ss.str();
}

Status ToDo_Service::GetList(ServerContext* context, const tds::GetListReq* request, tds::GetListRes* response) {
	std::lock_guard<std::mutex> lock(this->mutex_);

	for (auto todo : this->ToDos_) {
		response->add_todo()->CopyFrom(todo.second);
	}

	return Status::OK;
}

Status ToDo_Service::AddItem(ServerContext* context, const tds::AddItemReq* request, tds::AddItemRes* response) {
	std::lock_guard<std::mutex> lock(this->mutex_);
	tds::ToDo todo;
	todo.set_id(this->generate_id());
	todo.set_description(request->description());
	todo.set_status(tds::Status::PENDING);

	this->ToDos_[todo.id()] = todo;
	NotifyUsers(todo);
	return Status::OK;
}


Status ToDo_Service::UpdateItem(ServerContext* context, const tds::UpdateItemReq* request, tds::UpdateItemRes* response) {
	std::lock_guard<std::mutex> lock(this->mutex_);
	tds::ToDo todo = request->todo();
// 	if (todo.empty()) {
// 		return Status(grpc::StatusCode::INVALID_ARGUMENT, "ToDo object must be specified");
// 	}
	auto todo_find = this->ToDos_.find(todo.id());
	if (todo_find == this->ToDos_.end())
	{
		return Status(grpc::StatusCode::NOT_FOUND, "ToDo not found");
	}
	this->ToDos_[todo.id()] = todo;
	NotifyUsers(todo);
	return Status::OK;
}


Status ToDo_Service::StreamUpdateChange(ServerContext* context, const tds::StreamUpdateChangeReq* request, ServerWriter<tds::StreamUpdateChangeRes>* writer) {
	//const std::string todo_id = request->todo_id();

	{
		//std::lock_guard<std::mutex> lock(this->stream_mutex_);
		std::lock_guard<std::mutex> lock(this->mutex_);
		this->Users_.push_back(writer);
		//	if (todo_id.empty()) {
		//		return Status(grpc::StatusCode::INVALID_ARGUMENT, "ToDo object must be specified");
		//	}
		//	auto todo_find = this->ToDos_.find(todo_id);
		//	if (todo_find == this->ToDos_.end())
		//	{
		//		return Status(grpc::StatusCode::NOT_FOUND, "ToDo not found");
		//	}
		//	//this->ToDos_[todo.id()] = todo;

		//	tds::StreamUpdateChangeRes response;
		//	*(response.mutable_todo()) = todo_find->second;

			/*if (!writer->Write(response))
			{
				return Status::CANCELLED;
			}*/
	}

	while (!context->IsCancelled()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	{
		std::lock_guard<std::mutex> lock(this->mutex_);
		this->Users_.erase(std::remove(this->Users_.begin(), this->Users_.end(), writer), this->Users_.end());
	}
	return Status::OK;
}

void ToDo_Service::NotifyUsers(const tds::ToDo& todo) {
	std::lock_guard<std::mutex> lock(this->mutex_);
	tds::StreamUpdateChangeRes response;
	*(response.mutable_todo()) = todo;

	for (auto writer : this->Users_) {
		/*if (!writer->Write(res)) {

		}*/
		writer->Write(response);
	}
}