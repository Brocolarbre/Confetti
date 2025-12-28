#pragma once

class Command
{
private:
	bool m_reversible;

public:
	Command(bool reversible);
	virtual ~Command() = default;

	bool isReversible() const;

	virtual void run() const = 0;
	virtual void revert() const = 0;
};