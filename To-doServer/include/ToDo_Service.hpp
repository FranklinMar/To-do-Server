#pragma once

#include <unordered_map>
#include <string>
#include <mutex>
#include <chrono>

#include <grpcpp/grpcpp.h>
#include <grpcpp/server_context.h>
#include <grpcpp/support/status.h>
#include <google/protobuf/map.h>

#include "todo.grpc.pb.h"
#include "todo.pb.h"

namespace tds = ToDoService::v1;
using grpc::Status;
using grpc::ServerContext;
using grpc::ServerWriter;

class ToDo_Service final : public tds::ToDoService::Service {
public:
	ToDo_Service();
	Status GetList(ServerContext* context, const tds::GetListReq* request, tds::GetListRes* response) override;
	Status AddItem(ServerContext* context, const tds::AddItemReq* request, tds::AddItemRes* response) override;
	Status UpdateItem(ServerContext* context, const tds::UpdateItemReq* request, tds::UpdateItemRes* response) override;
	Status StreamUpdateChange(ServerContext* context, const tds::StreamUpdateChangeReq* request, ServerWriter<tds::StreamUpdateChangeRes>* writer) override;

private:
	std::unordered_map<std::string, tds::ToDo> ToDos_;
	std::vector<ServerWriter<tds::StreamUpdateChangeRes>*> Users_;
	std::mutex mutex_;
	std::mutex stream_mutex_;

	static std::string generate_id();
	void NotifyUsers(const tds::ToDo& todo);
};