/*
	* Manages servers, clients, loadbalancers && their connections
	* Manages packet flow between the network
*/
#include <vector>
#include <stack>
#include <memory>
#include <stdint.h>
#include "../component/components.hpp"

class EcsManager {
private:
	// ====== Entity =======
	std::stack<uint32_t> freeEntityIds;
	std::vector<uint32_t> entities;
	uint32_t entityIdCounter = 0;

	// ====== Components ======
	std::vector<std::unique_ptr<UpdateComponent>> updateComponents;
	std::vector<std::unique_ptr<MoveAndRotateComponent>> updateComponents;
	std::vector<std::unique_ptr<DrawableComponent>> updateComponents;
public:
	template<typename T>
	void addComponentToEntity(T component, uint32_t entityId);

	template<typename T>
	void deleteComponent(std::vector<std::unique_ptr<T>>& components, uint32_t entityId);

	void addEntity();


	
	EcsManager();
	~EcsManager();
};