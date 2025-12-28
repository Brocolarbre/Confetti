#pragma once

class UserInterfaceBackend
{
private:

public:
	virtual ~UserInterfaceBackend() = default;

	virtual void initialize() const = 0;
	virtual void terminate() const = 0;
	virtual void beginRender() const = 0;
	virtual void endRender() const = 0;
};