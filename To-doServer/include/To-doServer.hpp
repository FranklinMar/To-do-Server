// To-doServer.h : Include file for standard system include files,
// or project specific include files. 

#pragma once

#include <string>
#include <memory>
#include <vector>

#include <grpcpp/grpcpp.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/support/interceptor.h>
#include <grpcpp/support/server_interceptor.h>

#include "logger.hpp"

class Server {
public:
	explicit Server(std::string server_address, std::shared_ptr<grpc::Service> service = nullptr, std::string service_name = "Server");

	void Start();
	void Stop();

private:
	std::unique_ptr<grpc::Server> server_;
	std::shared_ptr<grpc::Service> service_;
	std::string server_address_;
	std::string service_name_;

	// Middle wares in grpc - Interceptors
	std::vector<std::unique_ptr<grpc::experimental::ServerInterceptorFactoryInterface>> interceptor_creators_;
};

//#include <iostream>
//
//namespace API_gRPC {
//
//	// Public function for starting gRPC-server
//	void runServer(const std::string& address, std::shared_ptr<storage::IStorageManager> pStoreManager);
//
//	// Public function for stop gRPC-server
//	void stopServer();
//}