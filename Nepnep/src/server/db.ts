import { PrismaClient } from '@prisma/client'

const mode = process.env.NODE_ENV

const createPrismaClient = () =>
    new PrismaClient({
        log: mode === "development" ? ["query", "error", "warn"] : ["error"]
    })

const globalForPrisma = globalThis as unknown as {
    prisma?: PrismaClient
}

export const db = globalForPrisma.prisma || createPrismaClient()

if (mode !== "production") globalForPrisma.prisma = db