#include <memory>

#include "analysis-core/internal/base.h"
#include "analysis-core/dataset.h"

using namespace AnalysisCore;

Dataset::Dataset(int& id) : id_(id){

}

std::shared_ptr<Dataset> Dataset::Create(int& id){
  return std::make_shared<Dataset>(id);
}

Dataset::~Dataset(){

}

int Dataset::GetId(){
  return id_;
}

std::shared_ptr<MemberBase> Dataset::GetMember(const std::string& name){
  return members_[name];
}

void Dataset::SetMember(const std::string& name, std::shared_ptr<MemberBase> member){
  members_[name] = member;
}