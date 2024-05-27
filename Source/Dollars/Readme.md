# Dollars MoCap in VClass

### VClass모듈에 Dollars가 적용되는 흐름은 다음과 같습니다. **볼드**는 구현해 주셔야할 사항을 표기한 내용입니다.

1. DollarsServerReceiver 액터가 BeginPlay에서 OSC서버를 UOSCServer로 생성
2. DollarsServerReceiver::OnOSCMessageReceived 함수를 생성한 UOSCServer객체의 OnOscMessageReceived 델리게이트에 다이나믹으로 바인딩
3. DollarsMono에서 언리얼 OSC로 데이터 스트리밍
4. OSC서버는 메시지를 받으면 바인딩된 OnOSCMessageReceived를 실행
5. **OnOSCMessageReceived 함수에선 받은 메세지의 주소(FOSCAddress UOSCManager::GetOSCMessageAddress(const FOSCMessage& message))와 실수값 배열(void UOSCManager::GetAllFloats(const FOSCMessage& message, TArray<float>& outValues))를 구함**
6. **5에서 구한 주소를 FString으로 변환(FString UOSCManager::GetOSCAddressFullPath(const FOSCAddress& InAddress))후 '/'문자를 기준으로 문자열 split(cullEmptyString = true)**
7. **각 구한 값을 oscFloatArray와 oscAddressArray에 저장**
8. **해당 값들을 MoCapData구조체에 담아 각 클라이언트 VClassClientController 하 DollarsClientReceiver 액터컴포넌트의 "ClientReceiveMoCapData" 함수로 전달**
9. 전달받은 값을 "moCapData"에 저장하고 "void UClientReceiver::MoCapMapping()" 함수 실행
10. **"MoCapMapping" 함수에서는 가장 먼저 Address 배열값을 통해 값의 유효성 검사를 실시(배열의 길이가 3 이상인가, 배열의 [0]값이 "Dollars"인가)**
11. **유효성 검사에서 이상이 없을 경우, Address 배열의 1번값을 검사하여 종류에 따라 실수값 배열을 dollarsMoCapActor 변수의 멤버로 매핑합니다.**
12. 이후 "UE4_Mannequin_Skeleton_VL_Blueprint" Anim 블루프린트에서 해당 dollarsMoCapActor값을 읽어와 "SK_Mannequin_CtrlRig"에 전달합니다.
13. "SK_Mannequin_CtrlRig"는 dollarsMoCapActor값을 실제 리깅에 적용합니다.


### "MoCapMapping" 함수에서 적용되는 규칙은 다음과 같습니다.

+ Address 배열의 [1]값은 "Skeleton","BoneControl","Ext" 세가지 값을 가질 수 있습니다.
+ "Skeleton"일 경우, 실수값 배열의 유효성 검사를 먼저 실시합니다.(실수값 배열의 길이가 3 이상인가)
  + 유효성 검사에서 이상이 없을 경우, 실수값 배열의 [0],[1],[2]의 값으로 FVector 하나를 생성하여 tempVector에 저장합니다.(각각 x,y,z값에 매핑)
    + 이후 Address 배열 [2]값을 검사하여, 해당 문자열에 대응하는 dollarsMoCapActor.skeleton 구조체의 멤버의 값으로 tempVector를 매핑합니다.
+ "BoneControl"일 경우, 실수값 배열의 유효성 검사를 먼저 실시합니다.(실수값 배열의 길이가 7 이상인가)
  + 유효성 검사에서 이상이 없을경우, dollarsMoCapActor.isReceived 값을 "true"로 설정하고 실수값 배열의 [0],[1],[2]의 값으로 FVector를 하나(각각 x,y,z값에 매핑), [3],[4],[5],[6]의 값으로 FQuat를 하나(각각 x,y,z,w값에 매핑) 생성하여, 두 값을 통해 FTransform을 하나 생성후 tempTransform에 저장합니다.
    + 이루 Address 배열 [2]값을 검사하여, 해당 문자열에 대응하는 dollarsMoCapActor.bonControls 구조체의 멤버의 값으로 tempTransform을 매핑합니다.
+ "Ext"일 경우, 실수값 배열의 유효성 검사없이 Address 배열 [2]값을 검사합니다.
  + Address 배열 [2]값은 "Visibility", "BlendShape" 두 가지 값을 가지며, 해당 값에 따라 실수값 배열을 dollarsMoCapActor에 다은과 같이 매핑합니다.
    + **"Visibility"일 경우**
    + 0  →   visibilityHead
    + 1  →   visibilityLeftHand
    + 2  →   visibilityRightHand
    + 3  →   visibilityHip
    + 4  →   visibilityLeftLeg
    + 5  →   visibilityRightLeg
    + **"BlendShape"일 경우**
    + 0  →  faceData.eyeBlinkLeft
    + 1  →  faceData.eyeLookDownLeft
    + 2  →  faceData.eyeLookInLeft
    + 3  →  faceData.eyeLookOutLeft
    + 4  →  faceData.eyeLookUpLeft
    + 5  →  faceData.eyeSquintLeft
    + 6  →  faceData.eyeWideLeft
    + 7  →  faceData.eyeBlinkRight
    + 8  →  faceData.eyeLookDownRight
    + 9  →  faceData.eyeLookInRight
    + 10  →  faceData.eyeLookOutRight
    + 11  →  faceData.eyeLookUpRight
    + 12  →  faceData.eyeSquintRight
    + 13  →  faceData.jawForward
    + 14  →  faceData.jawLeft
    + 15  →  faceData.jawRight
    + 16  →  faceData.jawOpen
    + 17  →  faceData.mouthClose
    + 18  →  faceData.mouthFunnel
    + 19  →  faceData.mouthPucker
    + 20  →  faceData.mouthLeft
    + 21  →  faceData.mouthRight
    + 22  →  faceData.mouthSmileLeft
    + 23  →  faceData.mouthSmileRight
    + 24  →  faceData.mouthFrownLeft
    + 25  →  faceData.mouthFrownRight
    + 26  →  faceData.mouthDimpleLeft
    + 27  →  faceData.mouthDimpleRight
    + 28  →  faceData.mouthStretchLeft
    + 29  →  faceData.mouthStretchRight
    + 30  →  faceData.mouthRollLower
    + 31  →  faceData.mouthRollUpper
    + 32  →  faceData.mouthShrugLower
    + 33  →  faceData.mouthShrugUpper
    + 34  →  faceData.mouthPressLeft
    + 35  →  faceData.mouthPressRight
    + 36  →  faceData.mouthLowerDownLeft
    + 37  →  faceData.mouthLowerDownRight
    + 38  →  faceData.mouthUpperUpLeft
    + 39  →  faceData.mouthUpperUpRight
    + 40  →  faceData.browDownLeft
    + 41  →  faceData.browDownRight
    + 42  →  faceData.browInnerUp
    + 43  →  faceData.browOuterUpLeft
    + 44  →  faceData.browOuterUpRight
    + 45  →  faceData.cheekPuff
    + 46  →  faceData.cheekSquintLeft
    + 47  →  faceData.cheekSquintRight
    + 48  →  faceData.noseSneerLeft
    + 49  →  faceData.noseSneerRight
