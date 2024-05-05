#pragma once

#include "Component.hpp"
#include "Node.hpp"
#include <memory>
#include <string>
#include <typeinfo>
#include <vector>

// TODO
class InputEvent;
///

class Script : public Component {
public:
	Script(const std::string& name = "");
	virtual ~Script() = default;

	virtual std::type_index getType() override;

	virtual void update(float delta_time) = 0;
	virtual void inputEvent(const InputEvent& input_event);
	virtual void resize(uint32_t width, uint32_t height);
};

class NodeScript : public Script {
public:
	NodeScript(Node& node, const std::string& name = "");
	virtual ~NodeScript() = default;

	Node& getNode();

private:
	Node& node;
};

Script::Script(const std::string& name) :
    Component{name}
{}

std::type_index Script::getType()
{
	return typeid(Script);
}

void Script::inputEvent(const InputEvent&)
{}

void Script::resize(uint32_t, uint32_t)
{}

NodeScript::NodeScript(Node& node, const std::string& name) :
    Script{name},
    node{node}
{}

Node& NodeScript::getNode()
{
	return node;
}
