/*
 * JetBrains-DiscordRichPresence
 * Copyright (C) 2022  Team HarTex and contributors
 *
 * JetBrains-DiscordRichPresence is free software: you can redistribute
 * it and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * JetBrains-DiscordRichPresence is distributed in the hope that it will
 * be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with JetBrains-DiscordRichPresence.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef NATIVE_FUNCTIONS_H
#define NATIVE_FUNCTIONS_H

#include <jni.h>
#include <string>

template<int LENGTH>
void
CreateNativeString(JNIEnv& jniEnv, jbyteArray bytes, char target[LENGTH]);

std::string
CreateNativeString(JNIEnv& jniEnv, jbyteArray bytes);

jbyteArray
CreateJavaString(JNIEnv& jniEnv, const char* string);

#endif
