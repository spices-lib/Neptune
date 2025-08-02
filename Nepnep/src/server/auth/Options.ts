import { PrismaAdapter } from '@auth/prisma-adapter'
import Credentials from 'next-auth/providers/credentials'
import { signInSchema } from '../../schemas'
import bcrypt from 'bcryptjs'
import { db } from '../DataBase'
import { DefaultSession, NextAuthOptions } from 'next-auth'

declare module 'next-auth' {
    interface Session extends DefaultSession {
        user: {
            id: string
        } & DefaultSession['user']
    }
}

export const authOptions = {
    providers: [
        Credentials({
            credentials: {
                email: {},
                password: {}
            },
            authorize: async (credentials) => {
                try {
                    const { email, password } = await signInSchema.parseAsync(credentials)

                    const user = await db.user.findUnique({
                        where: {
                            email: email
                        }
                    })

                    const passwordMatch = await bcrypt.compare(password, user?.password ?? '')

                    if(!passwordMatch) {
                        return null
                    }

                    return user

                } catch(error) {
                    return null
                }
            }
        }),
    ],
    session: {
        strategy: 'jwt'
    },
    adapter: PrismaAdapter(db),
    callbacks: {
        session: ({ session, token }) => ({
            ...session,
            user: {
                ...session.user,
                id: token.id
            }
        })
    }
} satisfies NextAuthOptions