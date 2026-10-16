#pragma once
#include <string>
#include <variant>

namespace d2fb {

template <typename T>
class Result {
public:
    static Result ok(T v) { return Result(std::move(v)); }
    static Result err(std::string e) { return Result(std::move(e)); }

    bool has_value() const { return std::holds_alternative<T>(v_); }
    const T& value() const { return std::get<T>(v_); }
    const std::string& error() const { return std::get<std::string>(v_); }

private:
    explicit Result(T v) : v_(std::move(v)) {}
    explicit Result(std::string e) : v_(std::move(e)) {}
    std::variant<T, std::string> v_;
};

template <>
class Result<void> {
public:
    static Result ok() { return Result(true, {}); }
    static Result err(std::string e) { return Result(false, std::move(e)); }
    bool has_value() const { return ok_; }
    const std::string& error() const { return err_; }
private:
    Result(bool ok, std::string e) : ok_(ok), err_(std::move(e)) {}
    bool ok_;
    std::string err_;
};

} // namespace d2fb