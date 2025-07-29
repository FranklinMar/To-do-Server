#include <iostream>
#include <memory>
#include <string>
 
#include "Config.hpp"
#include "To-doServer.hpp"
#include "ToDo_Service.hpp"

namespace tds = ToDoService::v1;

int main()
{
	try {
		Config config = Config::New();
		std::shared_ptr<ToDo_Service> TDService = std::make_shared<ToDo_Service>();
		std::unique_ptr<Server> server = std::make_unique<Server>(config.host + ":" + config.port, TDService, tds::ToDoService::service_full_name());

		server->Start();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}

Server::Server(std::string server_address, std::shared_ptr<grpc::Service> service, std::string service_name) : server_address_(server_address_), service_(service), service_name_(service_name) {
	// Register intercept
	//this->interceptor_creators_.emplace_back(std::make_unique<LoggerInterceptorFactory>());
}

void Server::Start() {
	grpc::ServerBuilder builder;

	builder.AddListeningPort(this->server_address_, grpc::InsecureServerCredentials());

	builder.RegisterService(this->service_.get());

	//builder.experimental().SetInterceptorCreators(std::move(this->interceptor_creators_));

	this->server_ = builder.BuildAndStart();

	std::cout << this->service_name_ << " listening on " << this->server_address_ << std::endl;

	this->server_->Wait();
}

void Server::Stop()
{
	std::cout << this->service_name_ << " shutting down." << std::endl;
	this->server_->Shutdown();
	std::cout << this->service_name_ << " is down." << std::endl;
}


//using API_gRPC::ServerGRPC;
//
//using grpc::Server;
//using grpc::ServerBuilder;
//
//ServerGRPC* pService = nullptr;
//std::unique_ptr<Server> pServer = nullptr;
//
//void api_grpc::runServer(const std::string& address,
//    std::shared_ptr<storage::IStorageManager> pStoreManager) {
//    // создаем свой сервис
//    pService = new  (pStoreManager);
//
//    // создаем gRPC-шный server builder
//    ServerBuilder serverBuilder;
//
//    // добавляем порт и специфицируем вид подключения (не защищенное)
//    serverBuilder.AddListeningPort(address, grpc::InsecureServerCredentials());
//
//    // регистрируем наш собственный сервис и запускаем
//    serverBuilder.RegisterService(pService);
//    pServer = serverBuilder.BuildAndStart();
//    std::cout << "Server listening on " << address << std::endl;
//
//    // этот метод является блокирующим
//    pServer->Wait();
//}
//
////! Public function for stop gRPC-server
//void api_grpc::stopServer() {
//    // этот метод завершит блокоирующий Wait()
//    pServer->Shutdown();
//
//    delete pService;
//    delete(pServer.release());
//}