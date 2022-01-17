#ifndef PROTOCOL_H
#define PROTOCOL_H

#endif // PROTOCOL_H

#define RunStateCode char
#define RSC RunStateCode

//word lenth
#define opPart_1                20
#define opPart_2                40
#define opPart_3                60
#define Length_Username         20
#define Length_Password         20
#define Length_Key              20

//run code
#define run_NoError             0
#define run_UnknowError         1
#define run_IllegalInput        2
#define run_FileExist           3
#define run_DirExist            4
#define run_FileUnexist         5
#define run_DirUnexist          6

//error code
#define noError                 0
#define error_IllegalIp         1
#define error_IllegalPort       2

//op code
#define opCode_noError          0
#define opCode_CreateUser       1
#define opCode_DeleteUser       2
#define opCode_ChangePassword   3
#define opCode_Login            4
#define opCode_WriteFile        5
#define opCode_ReadFile         6
#define opCode_DeleteFile       7
#define opCode_CreatePath       8
#define opCode_DeletePath       9
#define opCode_ServerExtend     127
#define opCode_RequestDir       255

//state code
#define stCode_Undefined            0
#define stCode_CreateUser           1
#define stCode_UserExist            2
#define stCode_DeleteUser           3
#define stCode_DeleteUserPWDFail    4
#define stCode_ChangePWD            5
#define stCode_ChangePWDFile        6
#define stCode_LoginSucceed         7
#define stCode_UserUnexist          8
#define stCode_LoginPWDError        9
#define stCode_UploadSucceed        10
#define stCode_DownloadReturn       11
#define stCode_FileUnexist          12
#define stCode_DeleteFileSucceed    13
#define stCode_ShearchFileFailed    14
#define stCode_PathCreateSucceed    15
#define stCode_PathExist            16
#define stCode_PathDeleteSucceed    17
#define stCode_PathUnexist          18
#define stCode_PermissionDenied     19
#define stCode_ServerExtendSucceed  127
#define stCode_GetFileTreeSucceed   255

//server returned code
#define svReturn_seccess        0
#define svReturn_UnknowError    1
#define svReturn_FileUnexist    2
#define svReturn_OpUnexist      3
