int main()
{
	__asm
	{
			mov eax,fs:[30h];
			mov eax,[eax+0ch]//Get the LDR
			mov eax,[eax+0xc]//Main.exe
			mov eax,[eax+0];///ntdll.dll
			mov eax,[eax+0];//kernel32.dll
			mov eax,[eax+18h];
			push eax;//保存的就是Kernel32.dll的地址 Kernel32.dll+1FF90 = GetProAddress
			//通过LoadLibrary获取其他dll的baseaddress
			//kernel32.dll+21C70=LoadLibrary;
			mov ebx,eax;
			add ebx,21C70h;    //LoadLibrary
			//获取user32.dll
			//自己构造字符串 user.dll
			push 27756
			push 1680749107
			push 1919251317
			mov eax,esp
			PUSH eax;
			CALL ebx;
			mov ecx,eax
				POP EAX	//维持平衡
				POP EAX
				POP EAX
			pop eax;
			add eax,0x1FF90
			//找到user32.dll的baseaddress了就可以通过GetProAddress获取MessageBoxA的函数地址了
			//PUSH func;//自己构造字符串 MessageBoxA
			PUSH 4290671
			PUSH 1113941857
			PUSH 1936942413
			PUSH ESP
			PUSH ECX //user32.dll handle
			CALL eax; // 函数返回值是MessageBoxA的函数地址
			//call messageboxa
				PUSH 0
				PUSH 0
				PUSH 0
				PUSH 0
				CALL EAX;
			POP EAX
			POP EAX
			POP EAX
	}
	return 0;
}
