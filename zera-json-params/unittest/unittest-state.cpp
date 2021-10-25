#include <gtest/gtest.h>

#include "zerajsonhelper.h"

#include "zera-json-params-structure.h"
#include "zera-json-params-state.h"

// positive: valid template / creete and check default
TEST(TEST_STATE,VALID_ALL_TYPES) {
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_STATE,VALID_ALL_TYPES");
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.loadStructure(jsonStructureRaw);
    EXPECT_EQ(errListStructure.isEmpty(), true) << "Expect no errors";
    if(errListStructure.isEmpty()) {
        cZeraJsonParamsState jsonParamState;
        jsonParamState.setStructure(jsonParamStructure.jsonStructure());
        QJsonObject jsonParamDefault = jsonParamState.createDefaultJsonState();
        QJsonObject jsonParamDefaultExpected = ZeraJsonHelper::loadFromQrc("TEST_STATE,VALID_ALL_TYPES_DEFAULT");
        EXPECT_EQ(jsonParamDefaultExpected, jsonParamDefaultExpected) << "Expected default params do not match";
    }
}

TEST(TEST_STATE,EMPTY_STRUCT) {
    QJsonObject jsonParamDummy;
    jsonParamDummy.insert("dummy", true);
    cZeraJsonParamsState jsonParamState;
    cZeraJsonParamsState::ErrList errList = jsonParamState.validateJsonState(jsonParamDummy);
    EXPECT_EQ(errList.count(), 1);
    for(auto err : errList){
        EXPECT_EQ(err.m_errType,cZeraJsonParamsState::errorTypes::ERR_INVALID_STRUCTURE);
    }
}

TEST(TEST_STATE,EMPTY_STATE) {
    // Load dummy but working structure
    QJsonObject jsonStructureRaw = ZeraJsonHelper::loadFromQrc("TEST_STATE,VALID_ALL_TYPES");
    cZeraJsonParamsStructure jsonParamStructure;
    cZeraJsonParamsStructure::ErrList errListStructure = jsonParamStructure.loadStructure(jsonStructureRaw);
    EXPECT_EQ(errListStructure.isEmpty(), true) << "Expect no errors";
    if(errListStructure.isEmpty()) {
        // Valiate empty state & expect empty state errror
        cZeraJsonParamsState jsonParamState;
        jsonParamState.setStructure(jsonParamStructure.jsonStructure());
        cZeraJsonParamsState::ErrList errList = jsonParamState.validateJsonState(QJsonObject());
        EXPECT_EQ(errList.count(), 1);
        for(auto err : errList){
            EXPECT_EQ(err.m_errType,cZeraJsonParamsState::errorTypes::ERR_EMPTY_STATE);
        }
    }
}

TEST(TEST_STATE,EMPTY_STATE_AND_STRUCT) {
    cZeraJsonParamsState jsonParamState;
    cZeraJsonParamsState::ErrList errList = jsonParamState.validateJsonState(QJsonObject());
    EXPECT_EQ(errList.count(), 2);
}

