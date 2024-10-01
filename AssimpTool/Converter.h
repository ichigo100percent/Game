#pragma once

class Converter
{
public:
	Converter();
	~Converter();

private:
	shared_ptr<Assimp::Importer> _importer;
};

