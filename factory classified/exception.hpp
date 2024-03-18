#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <exception>
#include <string>

class end_of_file : public std::exception{
public:
    const char* what() const noexcept override {
        return e.c_str();
    }

private:
    std::string e = "end of file";
};

class unknown_color : public std::exception{
public:
    unknown_color(const std::string & name):
        e( std::string( "unknown color [") + name + "]. ")
    {}

    const char* what() const noexcept override {
        return e.c_str();
    }

private:
    std::string e;
};

class invalid_position : public std::exception{
public:
    invalid_position(const std::string & type):
        e( std::string( "invalid position [") + type + "]. ")
    {}

    const char* what() const noexcept override {
        return e.c_str();
    }

private:
std::string e;
};

class unknown_shape : public std::exception{
public:
    unknown_shape(const std::string & name):
        e( std::string( "unknown shape [") + name + "]. ")
    {}

    const char* what() const noexcept override {
        return e.c_str();
    }

private:
std::string e;
};

class invalid_size : public std::exception{
public:
    invalid_size(const std::string & type):
        e( std::string( "invalid size [") + type + "]. ")
    {}

    const char* what() const noexcept override {
        return e.c_str();
    }

private:
std::string e;
};

class invalid_scale : public std::exception{
public:
    invalid_scale(const std::string & type):
        e( std::string( "invalid scale [") + type + "]. ")
    {}

    const char* what() const noexcept override {
        return e.c_str();
    }

private:
std::string e;
};

// class invalid_image : public std::exception{
// public:
//     invalid_image(const std::string & filename):
//         e( std::string( "invalid scale [") + filename + "]. ")
//     {}

//     const char* what() const noexcept override {
//         return e.c_str();
//     }

// private:
// std::string e;
// };

#endif // EXCEPTION_HPP