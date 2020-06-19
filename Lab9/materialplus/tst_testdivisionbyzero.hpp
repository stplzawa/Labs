#ifndef TST_TESTDIVISIONBYZERO_HPP
#define TST_TESTDIVISIONBYZERO_HPP

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <lockcontroller.h>


using namespace testing;

class MockIKeypad : public IKeypad {
public:
    MOCK_METHOD(bool, isActive, ());
    MOCK_METHOD(void, wait, ());
    MOCK_METHOD(PasswordResponse, requestPassword, ());
};

class MockILatch : public ILatch {
public:
    MOCK_METHOD(bool, isActive, ());
    MOCK_METHOD(DoorStatus, open, ());
    MOCK_METHOD(DoorStatus, close, ());
    MOCK_METHOD(DoorStatus, getDoorStatus, ());
};


TEST(labWork9, testWork1){

    MockILatch Hook;
    MockIKeypad Keypad;
    LockController Door(&Keypad, &Hook);
    EXPECT_CALL(Keypad, wait())
                .Times(1);
    Door.wait();
}


TEST(labWork9, testWork2){
    MockILatch Hook;
    MockIKeypad Keypad;
    LockController Door(&Keypad, &Hook);
    EXPECT_CALL(Hook, getDoorStatus())
                .Times(1)
                .WillOnce (Return(DoorStatus::CLOSE));
    EXPECT_FALSE(Door.isDoorOpen());
}

TEST(labWork9, testWork3){
    MockILatch Hook;
    MockIKeypad Keypad;
    LockController Door(&Keypad, &Hook);
    EXPECT_CALL(Hook, getDoorStatus())
                .Times(1)
                .WillOnce (Return(DoorStatus::OPEN));
    EXPECT_TRUE(Door.isDoorOpen());

}

TEST(labWork9, testWork4){
    MockILatch Hook;
    MockIKeypad Keypad;
    LockController Door(&Keypad, &Hook);
    EXPECT_CALL(Hook, open()) .Times(1);
    EXPECT_EQ(Door.unlockDoor(),DoorStatus::OPEN);

}


TEST(labWork9, testWork5){
   MockILatch Hook;
   MockIKeypad Keypad;
   LockController Door(&Keypad, &Hook);
   EXPECT_CALL(Hook, close())
                .Times(1)
                .WillOnce(Return(DoorStatus::CLOSE));
   EXPECT_EQ(Door.lockDoor(),DoorStatus::CLOSE);

}

TEST(labWork9, testWork6){
    MockILatch Hook;
    MockIKeypad Keypad;
    LockController Door(&Keypad, &Hook);
    EXPECT_CALL(Hook, isActive())
                .Times(1)
                .WillOnce(Return(1));
    EXPECT_CALL(Keypad, isActive())
                .Times(1)
                .WillOnce(Return(1));
    EXPECT_EQ(Door.hardWareCheck(),HardWareStatus::OK);
}

TEST(labWork9, testWork7){
    MockILatch Hook;
    MockIKeypad Keypad;
    LockController Door(nullptr, &Hook);
    EXPECT_CALL(Hook, isActive())
                .Times(AtLeast(0))
                .WillOnce(Return(1));
    EXPECT_CALL(Keypad, isActive())
                .Times(AtLeast(0))
                .WillOnce(Return(1));
    EXPECT_EQ(Door.hardWareCheck(),HardWareStatus::ERROR);

}

TEST(labWork9, testWork8){
    MockILatch Hook;
    MockIKeypad Keypad;
    LockController Door(&Keypad, &Hook);
    EXPECT_CALL(Hook, isActive())
                .Times(AtLeast(0))
                .WillOnce(Return(0));
    EXPECT_CALL(Keypad, isActive())
                .Times(AtLeast(0))
                .WillOnce(Return(1));
    EXPECT_EQ(Door.hardWareCheck(),HardWareStatus::ERROR);

}

TEST(labWork9, testWork9){
    MockILatch Hook;
    MockIKeypad Keypad;
    LockController Door(&Keypad, &Hook);
    PasswordResponse passResp{PasswordResponse::Status::OK,"0000"};
    EXPECT_CALL(Keypad, requestPassword())
                .Times(1)
                .WillOnce(Return(passResp));
    EXPECT_TRUE(Door.isCorrectPassword());
}

TEST(labWork9, testWork10){
    MockILatch Hook;
    MockIKeypad Keypad;
    LockController Door(&Keypad, &Hook);
    PasswordResponse passResp{PasswordResponse::Status::OK,"1111"};
    EXPECT_CALL(Keypad, requestPassword())
                .Times(1)
                .WillOnce(Return(passResp));
    EXPECT_FALSE(Door.isCorrectPassword());
}


TEST(labWork9, testWork11){
    MockILatch Hook;
    MockIKeypad IKeypad;
    LockController Door(&IKeypad, &Hook);
    PasswordResponse oldPass{PasswordResponse::Status::OK,"0000"};
    PasswordResponse newPass{PasswordResponse::Status::OK,"1111"};
    EXPECT_CALL(IKeypad, requestPassword())
            .Times(2)
            .WillOnce(Return(oldPass))
            .WillOnce(Return(newPass));
            Door.resetPassword();
    EXPECT_CALL(IKeypad, requestPassword()) .Times(1) .WillOnce(Return(newPass));
    EXPECT_TRUE(Door.isCorrectPassword());
}


TEST(labWork9, testWork12){
    MockILatch Hook;
    MockIKeypad Keypad;
    LockController Door(&Keypad, &Hook);
    EXPECT_CALL(Keypad, requestPassword()).Times(Exactly(5))
                .WillOnce(Return(PasswordResponse{PasswordResponse::Status::OK, "0000"}))
                .WillOnce(Return(PasswordResponse{PasswordResponse::Status::OK, "1111"}))
                .WillOnce(Return(PasswordResponse{PasswordResponse::Status::OK, "1111"}));
    Door.resetPassword();
    Door.resetPassword();
    ASSERT_TRUE(Door.isCorrectPassword());
}

#endif // TST_TESTDIVISIONBYZERO_HPP
