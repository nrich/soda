#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

#include <cstdint>
#include <map>
#include <memory>
#include <optional>
#include <variant>

enum class SimpleType {
    NONE,
    UNDEFINED,
    SCALAR
};

typedef std::variant<struct Struct, SimpleType> VariableType;

struct Struct {
    std::string name;
    std::vector<std::pair<std::string, VariableType>> slots;
    size_t size() const {
        return slots.size();
    }

    Struct(const std::string &name, std::vector<std::pair<std::string, VariableType>> slots) : name(name), slots(slots) {
    }

    bool operator==(const Struct &rhs) const {
        return name == rhs.name;
    }

    bool operator!=(const Struct &rhs) const {
        return name != rhs.name;
    }

    VariableType getType(const std::string &slot) const {
        for (const auto &s : slots) {
            if (s.first == slot)
                return s.second;
        }

        throw std::invalid_argument("Undefined slot `" + slot + "' in struct `" + name + "'");
        return SimpleType::NONE;
    }

    uint32_t getOffset(const std::string &slot) const {
        uint32_t i = 0;
        for (const auto &s : slots) {
            if (s.first == slot)
                return i;
            i++;
        }

        throw std::invalid_argument("Undefined slot `" + slot + "' in struct `" + name + "'");
        return 0;
    }
};

struct Function {
    const std::string name;
    const std::vector<std::pair<std::string, VariableType>> params;
    const VariableType returnType;

    Function(const std::string &name, std::vector<std::pair<std::string, VariableType>> params, VariableType returnType) : name(name), params(params), returnType(returnType) {
    }
};

class Environment {
    private:
        std::map<const std::string, std::pair<uint32_t, VariableType>> vars;
        std::map<const std::string, Function> functions;
        std::map<const std::string, Struct> structs;
        std::shared_ptr<Environment> parent;
        const int32_t offset;
    public:
        Environment(int32_t offset) : parent(NULL), offset(offset) {
        }

        Environment(std::shared_ptr<Environment> parent) : parent(parent), offset(0) {
        }

        Struct defineStruct(const std::string &name, std::vector<std::pair<std::string, VariableType>> slotlist) {
            auto _struct = Struct(name, slotlist);
            structs.insert(std::make_pair(name, _struct));
            return _struct;
        }

        Function defineFunction(const std::string &name, std::vector<std::pair<std::string, VariableType>> params, VariableType returnType) {
            auto function = Function(name, params, returnType);
            functions.insert(std::make_pair(name, function));
            return function;
        }

        Struct getStruct(const std::string &name) const {
            auto found = structs.find(name);
            if (found != structs.end()) {
                return found->second;
            } else {
                if (parent) {
                    return parent->getStruct(name);
                } else {
                    throw std::invalid_argument("Undefined struct `" + name + "'");
                }
            }
        }

        Function getFunction(const std::string &name) const {
            auto found = functions.find(name);
            if (found != functions.end()) {
                return found->second;
            } else {
                if (parent) {
                    return parent->getFunction(name);
                } else {
                    throw std::invalid_argument("Undefined function `" + name + "'");
                }
            }
        }


        const size_t Offset() const {
            return offset;
        }

        const size_t size() const {
            return vars.size();
        }

        uint32_t get(const std::string &name) const {
            auto found = vars.find(name);

            if (found != vars.end()) {
                return found->second.first;
            } else {
                if (parent) {
                    return parent->get(name);
                } else {
                    throw std::invalid_argument("Unknown variable `" + name + "'");
                }
            }
        }

        VariableType getType(const std::string &name) const {
            auto found = vars.find(name);

            if (found != vars.end()) {
                return found->second.second;
            } else {
                if (parent) {
                    return parent->getType(name);
                } else {
                    throw std::invalid_argument("Unknown variable `" + name + "'");
                }
            }
        }


        bool isStruct(const std::string &name) {
            auto found = structs.find(name);

            if (found != structs.end()) {
                return true;
            } else if (parent) {
                return parent->isStruct(name);
            }

            return false;
        }

        bool isFunction(const std::string &name) {
            auto found = functions.find(name);

            if (found != functions.end()) {
                return true;
            } else if (parent) {
                return parent->isFunction(name);
            }

            return false;
        }


        bool isGlobal(const std::string &name) {
            auto found = vars.find(name);

            if (found != vars.end() && parent) {
                return false;
            }

            return true;
        }

        int32_t create(const std::string &name, VariableType type, size_t count=1) {
            auto existing = vars.find(name);
            if (existing != vars.end()) {
                return existing->second.first;
            }

            int32_t next = Offset() + vars.size();
            for (size_t i = 0; i  < count; i++) {
                vars.insert(std::make_pair(name + std::string(i, ' '), std::make_pair(next+i, type)));
            }
            return next;
        }

        uint32_t set(const std::string &name, VariableType type) {
            auto found = vars.find(name);

            if (found != vars.end()) {
                //vars[name] = std::make_pair(found->second.first, type);
                found->second.second = type;
                return found->second.first;
            } else {
                if (parent) {
                    return parent->get(name);
                } else {
                    throw std::invalid_argument("Unknown variable `" + name + "'");
                }
            }
        }

        std::shared_ptr<Environment> Parent() const {
            return parent;
        }


        bool inFunction() const {
            return parent ? true : false;
        }
};

#endif //__ENVIRONMENT_H__
