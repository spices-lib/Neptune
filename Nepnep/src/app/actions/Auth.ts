'use server'

import { signUpSchema } from '../../Schemas'
import { ZodError } from 'zod'
import { db } from '../../server/DataBase'
import bcrypt from 'bcryptjs'
import { signIn, signOut } from '../../server/auth'

export async function signout() {
    await signOut()
}

export async function authenticate(
    prevState: string | undefined,
    formData: FormData
) {
    try {
        await signIn('credentials', formData)
    } catch (error) {
        if (error instanceof Error) {
            switch (error.name) {
                case 'CredentialsSignin':
                    return 'Invalid credentials'
                default:
                    return 'Something went wrong'
            }
        }
        throw error
    }
}

export async function register(
    prevState: string | undefined,
    formData: FormData
) {
    try {
        const {email, password} = await signUpSchema.parseAsync({
            email: formData.get('email'),
            password: formData.get('password')
        })

        const user = await db.user.findUnique({
            where: {
                email: email
            }
        })

        if(user) {
            return 'User already exist'
        }

        const hash = await bcrypt.hash(password, 10)

        await db.user.create({
            data: {
                email: email,
                password: hash
            }
        })

    } catch (error) {
        console.log(error)
        if(error instanceof ZodError) {
            return error.message
        }
    }
}