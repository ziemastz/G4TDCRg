#include "Run.hh"

Run::Run()
{

}

Run::~Run()
{

}
void Run::Merge(const G4Run *run)
{
    const Run* localRun = static_cast<const Run*>(run);
    
    //add counts to global data
    //fHitCount += localRun->fHitCount; 

    G4Run::Merge(run);
}

void Run::EndOfRun()
{
}
